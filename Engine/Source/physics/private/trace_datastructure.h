#pragma once
#include "physics/rigid_body.h"
#include "core/logger/log.h"
#include "core/time/time.h"
#include <array>

class TraceAccelerationDatastructure
{
	std::vector<std::shared_ptr<physics::RigidBody>> physic_bodies;

	struct NodeAABB
	{
		math::Vec2<float> min;
		math::Vec2<float> max;
	};

	struct GridNode
	{
		
	};

	NodeAABB merge_aabbs()
	{
		auto local_aabb = static_cast<NodeAABB*>(alloca(omp_get_max_threads() * sizeof(NodeAABB)));

#pragma omp parallel for
		for (auto i = 0; i < int(physic_bodies.size()); ++i)
		{
			const physics::AABBHull& aabb = physic_bodies[i]->get_hull();

			NodeAABB& local = local_aabb[omp_get_thread_num()];
			local.min.x = local.min.x > aabb.offset.x ? aabb.offset.x : local.min.x;
			local.min.x = local.min.y > aabb.offset.y ? aabb.offset.y : local.min.y;
			local.max.x = local.max.x > aabb.offset.x + aabb.extends.x ? aabb.offset.x + aabb.extends.x : local.max.x;
			local.max.y = local.max.y < aabb.offset.y + aabb.extends.y ? aabb.offset.y + aabb.extends.y : local.max.y;
		}

		NodeAABB result_aabb;
		for (uint32 i = 0; i < uint32(omp_get_max_threads()); ++i)
		{
			NodeAABB& local = local_aabb[i];
			result_aabb.min.x = result_aabb.min.x > local_aabb->min.x ? local_aabb->min.x : result_aabb.min.x;
			result_aabb.min.x = result_aabb.min.y > local_aabb->min.y ? local_aabb->min.y : result_aabb.min.y;
			result_aabb.max.x = result_aabb.max.x > local_aabb->max.x ? local_aabb->max.x : result_aabb.max.x;
			result_aabb.max.y = result_aabb.max.y < local_aabb->max.y ? local_aabb->max.y : result_aabb.max.y;
		}
		return result_aabb;
	}

	void build_grid(std::vector<std::shared_ptr<physics::RigidBody>>& rigid_bodies, NodeAABB& bounding_box)
	{

	}

public:
	TraceAccelerationDatastructure() = default;

	void add_rigid_body(std::shared_ptr<physics::RigidBody> rigid_body)
	{
		physic_bodies.push_back(rigid_body);
	}

	void remove_rigid_body(std::shared_ptr<physics::RigidBody> rigid_body)
	{
	}

	void build()
	{
		std::sort(physic_bodies.begin(), physic_bodies.end(),
			[](std::shared_ptr<physics::RigidBody>& a, std::shared_ptr<physics::RigidBody>& b)
		{
			return a->get_hull().offset.x < b->get_hull().offset.x;
		});
	}

	std::vector<physics::Contact> get_contacts()
	{
		std::vector<std::vector<std::pair<physics::RigidBody*, physics::RigidBody*>>> local_collision_pairs;
		local_collision_pairs.resize(omp_get_max_threads());

		std::vector<std::pair<physics::RigidBody*, physics::RigidBody*>> collision_pairs;
		collision_pairs.reserve(int(physic_bodies.size() * 0.25f));
#pragma omp parallel for schedule(guided, 1)
		for (int i = int(physic_bodies.size()) - 2; i >= 0; --i)
		{
			physics::RigidBody* body = physic_bodies[i].get();
			const float x_end = body->get_hull().extends.x + body->get_hull().offset.x; // TODO Transform offset not applied
			const float pos_y = body->get_hull().offset.y;
			const float end_y = pos_y + body->get_hull().extends.y;

			uint32 j = i + 1;
			physics::RigidBody* check_body = physic_bodies[j].get();

			// Iterate through all succeeding rigidbodies (in positiv x projection)
			while (j < physic_bodies.size() && x_end >= check_body->get_hull().offset.x)
			{
				check_body = physic_bodies[j].get();

				const float check_body_pos_y = check_body->get_hull().offset.y;
				const bool y_overlap = pos_y <= check_body_pos_y // Is body below check_body on y-Axis?
					? check_body_pos_y <= end_y // Yes, then the top of body must be higher than the bottom of check_body
					: pos_y <= check_body_pos_y + check_body->get_hull().extends.y; // No, then other way around
				if (y_overlap)
				{
					local_collision_pairs[omp_get_thread_num()].emplace_back(body, check_body);
				}
				j++;
			}
		}

		for (uint32 i = 0; i < omp_get_max_threads(); ++i)
		{
			collision_pairs.insert(collision_pairs.end(), local_collision_pairs[i].begin(), local_collision_pairs[i].end());
		}
		// 2. Narrow phase
		std::vector<physics::Contact> contacts;
#pragma omp parallel for schedule(dynamic)
		for (int i = 0; i < int(collision_pairs.size()); ++i)
		{
			physics::RigidBody* body_a = collision_pairs[i].first;
			physics::RigidBody* body_b = collision_pairs[i].second;
			physics::intersection::IntersectionData data;
			physics::intersection::AABB aabb_a{
				body_a->get_hull().offset,
				body_a->get_hull().extends * 0.5f
			};
			physics::intersection::AABB aabb_b{
				body_b->get_hull().offset,
				body_b->get_hull().extends * 0.5f
			};
			//if(body_a->get_collision_bodies()[0].collide_with(body_b->get_collision_bodies()[0], &data))
			if (physics::intersection::intersect_aabb_aabb(std::move(aabb_a), std::move(aabb_b), &data))
			{
#pragma omp critical
				contacts.emplace_back(collision_pairs[i], data.normal, data.penetration);
			}
		}

		return contacts;
	}
};
