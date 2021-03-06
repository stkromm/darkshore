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
			hull = { {0, 0}, {0, 0} };
			for (auto& c : bodies)
			{
				hull.merge(c.hull);
			}
			aabb_offset = hull.offset;
		}

		RigidBody::~RigidBody()
			= default;

		void RigidBody::add_collider(CollisionBody collider)
		{
			hull.merge(collider.hull);
			aabb_offset = hull.offset;
			collision_bodies.push_back(collider);
		}

		void RigidBody::remove_collider(CollisionBody collider)
		{
			uint32 to_be_removed = -1;
			hull = { {0, 0}, {0, 0} };
			uint32 i = 0;
			for (auto& c : collision_bodies)
			{
				if (to_be_removed == -1 && c.hull.to_string() == collider.hull.to_string()) {
					to_be_removed = i;
				}
				else {
					hull.merge(c.hull);
				}
				++i;
			}
			aabb_offset = hull.offset;
			collision_bodies.erase(collision_bodies.begin() + to_be_removed);
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