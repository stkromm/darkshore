#include <utility>
#include "physics/rigid_body.h"

using namespace physics;

RigidBody::RigidBody(std::shared_ptr<Transform> transform, std::vector<CollisionBody> bodies) : transform(std::move(
	                                                                                                transform)),
                                                                                                collision_bodies(bodies)
{
	for (auto& c : bodies)
	{
		hull.merge(c.hull);
	}
	aabb_offset = hull.offset;
	//hull.offset += transform->get_position();
}

RigidBody::~RigidBody()
= default;

void RigidBody::add_collider(CollisionBody collider)
{
	hull.merge(collider.hull);
	aabb_offset = hull.offset;
	//hull.offset += transform->get_position();
	collision_bodies.push_back(collider);
}

void RigidBody::remove_collider(CollisionBody collider)
{
	hull = {{0, 0}, {0, 0}};
	for (auto& c : collision_bodies)
	{
		hull.merge(c.hull);
	}
	aabb_offset = hull.offset;
	//hull.offset += transform->get_position();
}

void RigidBody::add_force(const math::FVec2 force)
{
	asleep = false;
	linear_force_acc += force;
}

void RigidBody::add_impuls(const math::FVec2 impuls)
{
	asleep = false;
	linear_impuls_acc += impuls;
}

void RigidBody::move(const math::FVec2 move)
{
	asleep = false;
	translation += move;
}

void RigidBody::integrate(const float delta)
{
	if (asleep)
	{
		return;
	}

	math::FVec2 acceleration_acc;
	if (ignore_mass)
	{
		acceleration_acc += linear_force_acc;
	}
	else
	{
		acceleration_acc += linear_force_acc * inversed_mass;
	}
	linear_force_acc = {0, 0};

	velocity += acceleration_acc * delta;
	velocity = velocity * powf(linear_damping, delta);

	if (ignore_mass)
	{
		velocity += linear_impuls_acc;
	}
	else
	{
		velocity += linear_impuls_acc * inversed_mass;
	}
	linear_impuls_acc = {0, 0};

	transform->translate(translation + velocity * delta);

	if (is_nearly_zero(velocity) && is_nearly_zero(translation))
	{
		asleep = true;
	}

	translation.x = 0;
	translation.y = 0;
	hull.offset = transform->get_position() + aabb_offset;
}

void RigidBody::set_velocity(const math::FVec2 collider_velocity)
{
	this->velocity = collider_velocity;
}
