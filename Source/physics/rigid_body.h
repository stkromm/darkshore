#pragma once

#include <vector>

#include "transform.h"
#include "math/vec2.h"

namespace physics {
	struct AABBHull
	{
		/**
		Offset relative offset to transform position
		*/
		math::Vec2 offset;
		/**
		Size of the aabb hull
		*/
		math::Vec2 extends;

		std::string to_string() const
		{
			std::stringstream ss;
			ss << "AABBHull(Offset:" << offset.x << "," << offset.y << ";Extends:" << extends.x << "," << extends.y << ")";
			return ss.str();
		}

		void merge(AABBHull& hull)
		{
			if (offset.x > hull.offset.x)
			{
				offset.x = hull.offset.x;
			}
			if (offset.x + extends.x < hull.offset.x + hull.extends.x)
			{
				extends.x = hull.offset.x + hull.extends.x - offset.x;
			}

			if (offset.y > hull.offset.y)
			{
				offset.y = hull.offset.y;
			}
			if (offset.y + extends.y < hull.offset.y + hull.extends.y)
			{
				extends.y = hull.offset.y + hull.extends.y - offset.y;
			}
		}
	};

	class CollisionBody {
	public:
		AABBHull hull;
	};

	class RigidBody
	{
	private:
		AABBHull hull = { {-48,-64},{ 96, 128 } };
		std::shared_ptr<Transform> transform;
		std::vector<CollisionBody> collision_bodies;

		bool ignore_mass = false;
		bool asleep = true;
		float inversed_mass = 1.f;
		float linear_damping = 0.f;

		math::Vec2 translation = { 0,0 };
		math::Vec2 velocity = { 0,0 };
		math::Vec2 acceleration = { 0,0 };

		math::Vec2 linear_impuls = { 0,0 };
		math::Vec2 linear_impuls_acc = { 0,0 };

		math::Vec2 linear_force = { 0,0 };
		math::Vec2 linear_force_acc = { 0,0 };

	public:
		RigidBody(std::shared_ptr<Transform> transform, std::vector<CollisionBody> bodies = {});
		~RigidBody();

		void add_force(math::Vec2 force);
		void add_impuls(math::Vec2 impuls);
		void move(math::Vec2 move);
		void integrate(const float millis);

		std::vector<CollisionBody> get_collision_bodies() const
		{
			return collision_bodies;
		}
		
		void add_collider(CollisionBody collider)
		{
			collision_bodies.push_back(collider);
			hull.merge(collider.hull);
		}

		void remove_collider(CollisionBody collider)
		{
			hull = { { 0,0 },{ 0,0 } };
			for (auto& c : collision_bodies)
			{
				hull.merge(c.hull);
			}
		}

		AABBHull get_hull() const
		{
			return hull;
		}

		void set_linea_damping(float damping)
		{
			linear_damping = damping;
		}

		bool is_asleep() const 
		{
			return asleep;
		}

		void set_mass(float mass) 
		{
			inversed_mass = 1 / mass;
		}

		Transform& get_transform() const 
		{
			return *transform;
		}
	};
}