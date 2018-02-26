#pragma once

#include <vector>
#include <omp.h>
#include <algorithm>

#include "collision.h"
#include "rigid_body.h"

namespace physics {
	class PhysicSimulation {
		std::vector<RigidBody> physic_bodies;
	public:

		void tick(float delta)
		{
			// Integration
#pragma omp parallel for schedule(dynamic)
			for (int i = 0; i < physic_bodies.size(); ++i)
			{
				physic_bodies[i].integrate(delta);
			}

			// Collision detection
			//
			// 1. Broad phase, find rigidbody pairs that might collide
			//
			// 1.1 sort rigidbodies by x value
			std::sort(physic_bodies.begin(), physic_bodies.end(), [](RigidBody& a, RigidBody& b) {
				return a.get_transform().get_position().x > b.get_transform().get_position().x;
			});

			std::vector<std::pair<RigidBody, RigidBody>> collision_pairs;
			for (int i = 0; i < physic_bodies.size() - 1; ++i)
			{

				int j = i + 1;
				while (j < physic_bodies.size() /* && aabb hull of rigidbody could be intersected*/)
				{
					// Iterate through all succeeding rigidbodies (in positiv x projection)
					bool y_overlap = false;
					if (y_overlap)
					{
						//#pragma omp critical
						//collision_pairs.push_back({a,b});
					}
					j++;
				}
			}

			// 2. Narrow phase
			std::vector<Contact> contacts;
			for (int i = 0; i < collision_pairs.size(); ++i)
			{
				for (auto& a : collision_pairs[i].first.get_collision_bodies())
				{
					for (auto& b : collision_pairs[i].second.get_collision_bodies())
					{
						//if (trace(a, b))
						//#pragma omp critical
						//	contacts.push_back({collision_pairs[i], a, b})
					}
				}
			}

			// 3. Contact resolution
			for (auto contact : contacts)
			{
				// Collision::resolve(contact);
			}
		}
	};
}