#pragma once

#include <vector>

#include "core/transform.h"
#include "core/math/vec2.h"

#include "physics/aabb_hull.h"
#include "physics/collision_body.h"

namespace ds {
	namespace physics {
		class RigidBody
		{
		private:
			std::shared_ptr<Transform> transform;
			ds::FVec2 aabb_offset = { -48, -64 };
			AABBHull hull = { {-48, -64}, {96, 128} };
			std::vector<CollisionBody> collision_bodies;

			bool ignore_mass = true;
			bool asleep = true;
			float inversed_mass = 0.f;
			float linear_damping = 0.f;

			ds::FVec2 translation = { 0, 0 };
			ds::FVec2 velocity = { 0, 0 };
			ds::FVec2 acceleration = { 0, 0 };

			ds::FVec2 linear_impuls = { 0, 0 };
			ds::FVec2 linear_impuls_acc = { 0, 0 };

			ds::FVec2 linear_force = { 0, 0 };
			ds::FVec2 linear_force_acc = { 0, 0 };

		public:
			explicit RigidBody(std::shared_ptr<Transform> transform, std::vector<CollisionBody> bodies = {});
			~RigidBody();

			void add_force(ds::FVec2 force);
			void add_impuls(ds::FVec2 impuls);
			void move(ds::FVec2 move);
			void integrate(float delta);

			std::vector<CollisionBody> get_collision_bodies() const
			{
				return collision_bodies;
			}

			void add_collider(CollisionBody collider);

			void remove_collider(CollisionBody collider);

			const AABBHull& get_hull() const
			{
				return hull;
			}

			float get_inversed_mass() const
			{
				return inversed_mass;
			}

			bool is_kinematic() const
			{
				return false;
			}

			const ds::FVec2& get_velocity() const
			{
				return velocity;
			}

			void set_linea_damping(const float damping)
			{
				linear_damping = damping;
			}

			bool is_asleep() const
			{
				return asleep;
			}

			void set_mass(const float mass)
			{
				inversed_mass = 1 / mass;
			}

			void set_inverse_mass(const float inversed_mass)
			{
				this->inversed_mass = inversed_mass;
			}

			Transform& get_transform() const
			{
				return *transform;
			}

			void set_velocity(ds::FVec2 collider_velocity);
			const ds::FVec2& get_impuls() const
			{
				return linear_impuls;
			}
		};
	}
}