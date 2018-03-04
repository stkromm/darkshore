#pragma once

#include <chrono>
#include <vector>
#include <omp.h>
#include <memory>
#include <algorithm>

#include "collision.h"
#include "rigid_body.h"

namespace physics {

	static std::vector<std::shared_ptr<RigidBody>> physic_bodies = {};
	class PhysicSimulation {
	public:
		static bool init()
		{
			physic_bodies = {};
			return true;
		}

		static void shutdown()
		{
			physic_bodies.clear();
		}

		static void add_rigid_body(std::shared_ptr<RigidBody> rigid_body)
		{
			physic_bodies.push_back(rigid_body);
		}

		static void tick(float delta)
		{
			// Integration
#pragma omp parallel for schedule(dynamic)
			for (int i = 0; i < (int)physic_bodies.size(); ++i)
			{
				physic_bodies[i]->integrate(delta);
			}

			// Collision detection
			//
			// 1. Broad phase, find rigidbody pairs that might collide
			//
			// 1.1 sort rigidbodies by x value
			std::sort(physic_bodies.begin(), physic_bodies.end(),
				[](std::shared_ptr<RigidBody>& a, std::shared_ptr<RigidBody>& b)
				{
					return a->get_transform().get_position().x + a->get_hull().offset.x < b->get_transform().get_position().x + b->get_hull().offset.x;
				});
		
			std::vector<std::pair<RigidBody*, RigidBody*>> collision_pairs;
			collision_pairs.reserve((int)(physic_bodies.size() * 0.25f));
#pragma omp parallel for schedule(dynamic)
			for (int i = 0; i < physic_bodies.size() - 1; ++i)
			{
				RigidBody* body = physic_bodies[i].get();
				float x_end = body->get_transform().get_position().x + body->get_hull().extends.x + body->get_hull().offset.x;
				float pos_y = body->get_transform().get_position().y + body->get_hull().offset.y;
				float height = body->get_hull().extends.y;
				int j = i + 1;
				RigidBody* check_body = physic_bodies[j].get();

				// Iterate through all succeeding rigidbodies (in positiv x projection)
				while (j < physic_bodies.size() && x_end >= check_body->get_transform().get_position().x + check_body->get_hull().offset.x)
				{
					check_body = physic_bodies[j].get();

					float check_body_pos_y = check_body->get_transform().get_position().y + check_body->get_hull().offset.y;
					bool y_overlap = pos_y < check_body_pos_y ?
						check_body_pos_y <= pos_y + height : pos_y <= check_body_pos_y + check_body->get_hull().extends.y;
					if (y_overlap)
					{
#pragma omp critical
						collision_pairs.push_back({ body, check_body });
					}
					j++;
				}
			}
			
			// 2. Narrow phase
			/*std::vector<Contact> contacts;
			for (int i = 0; i < collision_pairs.size(); ++i)
			{
				for (auto& a : collision_pairs[i].first.get_collision_bodies())
				{
					for (auto& b : collision_pairs[i].second.get_collision_bodies())
					{
						//if (trace(a, b)) {
						//#pragma omp critical
						//	contacts.push_back({collision_pairs[i], a, b});}
					}
				}
			}

			// 3. Contact resolution
			for (auto contact : contacts)
			{
				// Collision::resolve(contact);
			}*/

		}
	};
}