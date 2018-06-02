#include <utility>
#include "physics/rigid_body.h"

namespace ds
{
	namespace physics
	{

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
			hull = { {0, 0}, {0, 0} };
			for (auto& c : collision_bodies)
			{
				hull.merge(c.hull);
			}
			aabb_offset = hull.offset;
			//hull.offset += transform->get_position();
		}

		void RigidBody::add_force(const ds::FVec2 force)
		{
			asleep = false;
			linear_force_acc += force;
		}

		void RigidBody::add_impuls(const ds::FVec2 impuls)
		{
			asleep = false;
			linear_impuls_acc += impuls;
		}

		void RigidBody::move(const ds::FVec2 move)
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

			ds::FVec2 acceleration_acc;
			if (ignore_mass)
			{
				acceleration_acc += linear_force_acc;
			}
			else
			{
				acceleration_acc += linear_force_acc * inversed_mass;
			}
			linear_force_acc.set(0.f, 0.f);

			velocity += acceleration_acc * delta;
			velocity = velocity * std::pow(linear_damping, delta);

			if (ignore_mass)
			{
				velocity += linear_impuls_acc;
			}
			else
			{
				velocity += linear_impuls_acc * inversed_mass;
			}
			linear_impuls_acc.set(0.f, 0.f);

			transform->translate(translation + (velocity * delta));

			if (is_nearly_zero(velocity) && is_nearly_zero(translation))
			{
				asleep = true;
			}

			translation.set(0.f, 0.f);
			hull.offset = transform->get_position() + aabb_offset;
		}

		void RigidBody::set_velocity(const ds::FVec2 collider_velocity)
		{
			this->velocity = collider_velocity;
		}

	}
}