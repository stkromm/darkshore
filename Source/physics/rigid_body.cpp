#include "rigid_body.h"

using namespace physics;

RigidBody::RigidBody()
{
}

RigidBody::~RigidBody()
{
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

	velocity += acceleration_acc * delta;
	velocity = velocity * powf(linear_damping, delta);
	if (ignore_mass)
	{
		velocity += linear_impuls_acc;
	}
	else
	{
		velocity += linear_force_acc * inversed_mass;
	}

	transform->set_interpolation_velocity(velocity);
	transform->translate(translation + velocity * delta);
	translation = math::Vec2(0, 0);

	if (is_nearly_zero(velocity) && is_nearly_zero(translation))
	{
		asleep = true;
	}
}