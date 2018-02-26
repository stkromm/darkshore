#pragma once

#include <vector>

#include "transform.h"
#include "math/vec2.h"

namespace physics {
	struct CollisionBody {
	
	};
	class RigidBody
	{
	private:
		Transform * transform;
		std::vector<CollisionBody> collision_bodies;

		bool ignore_mass;
		bool asleep;
		float inversed_mass;
		float linear_damping;

		math::Vec2 translation;
		math::Vec2 velocity;
		math::Vec2 acceleration;

		math::Vec2 linear_impuls;
		math::Vec2 linear_impuls_acc;

		math::Vec2 linear_force;
		math::Vec2 linear_force_acc;

	public:
		RigidBody();
		~RigidBody();

		void add_force(math::Vec2 force);
		void add_impuls(math::Vec2 impuls);
		void move(math::Vec2 move);
		void integrate(const float millis);
		std::vector<CollisionBody>& get_collision_bodies() const;
		bool is_asleep() const {
			return asleep;
		}
		void set_mass(float mass) {
			inversed_mass = 1 / mass;
		}
		Transform& get_transform() const {
			return *transform;
		}
	};
}