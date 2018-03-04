#include "rigid_body.h"

using namespace physics;

RigidBody::RigidBody(std::shared_ptr<Transform> transform, std::vector<CollisionBody> bodies) : transform(transform), collision_bodies(bodies)
{
	for (auto& c : bodies)
	{
		hull.merge(c.hull);
	}
}

RigidBody::~RigidBody()
{
}

void RigidBody::add_force(math::Vec2 force)
{
	asleep = false;
	linear_force_acc += force;
}
void RigidBody::add_impuls(math::Vec2 impuls)
{
	asleep = false;
	linear_impuls_acc += impuls;
}
void RigidBody::move(math::Vec2 move)
{
	asleep = false;
	translation += move;
}

void RigidBody::integrate(const float delta) {
	if (asleep) {
		return;
	}

	math::Vec2 acceleration_acc;
	if (ignore_mass)
	{
		acceleration_acc += linear_force_acc;
	}
	else
	{
		acceleration_acc += linear_force_acc * inversed_mass;
	}
	linear_force_acc = { 0,0 }; 

	velocity += acceleration_acc * delta;
	velocity = velocity * powf(linear_damping, delta * 0.001f);

	if (ignore_mass)
	{
		velocity += linear_impuls_acc;
	}
	else
	{
		velocity += linear_impuls_acc * inversed_mass;
	}
	linear_impuls_acc = { 0,0 };

	transform->translate(translation + velocity * delta);
	translation = math::Vec2(0, 0);

	if (is_nearly_zero(velocity) && is_nearly_zero(translation))
	{
		asleep = true;
	}
}