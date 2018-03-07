#include "physics/physics.h"

#include <chrono>
#include <vector>
#include <omp.h>
#include <algorithm>

#include "physics/private/contact.h"
#include "physics/intersection.h"

static std::vector<std::shared_ptr<physics::RigidBody>> physic_bodies = {};
bool physics::init()
{
	physic_bodies = {};
	return true;
}

void physics::shutdown()
{
	physic_bodies.clear();
}

void physics::add_rigid_body(std::shared_ptr<RigidBody> rigid_body)
{
	physic_bodies.push_back(rigid_body);
}

void physics::tick(float delta)
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
	for (int i = 0; i < (int)physic_bodies.size() - 1; ++i)
	{
		RigidBody* body = physic_bodies[i].get();
		float x_end = body->get_transform().get_position().x + body->get_hull().extends.x + body->get_hull().offset.x;
		float pos_y = body->get_transform().get_position().y + body->get_hull().offset.y;
		float height = body->get_hull().extends.y;
		int j = i + 1;
		RigidBody* check_body = physic_bodies[j].get();

		// Iterate through all succeeding rigidbodies (in positiv x projection)
		while (j < (int)physic_bodies.size() && x_end >= check_body->get_transform().get_position().x + check_body->get_hull().offset.x)
		{
			check_body = physic_bodies[j].get();

			float check_body_pos_y = check_body->get_transform().get_position().y + check_body->get_hull().offset.y;
			bool y_overlap = pos_y < check_body_pos_y ?
				check_body_pos_y <= pos_y + height : pos_y <= check_body_pos_y + check_body->get_hull().extends.y;
			if (y_overlap)
			{
#pragma omp critical
				collision_pairs.emplace_back(body, check_body);
			}
			j++;
		}
	}

	// 2. Narrow phase
	std::vector<Contact> contacts;
	for (int i = 0; i < (int)collision_pairs.size(); ++i)
	{
		RigidBody* body_a = collision_pairs[i].first;
		RigidBody* body_b = collision_pairs[i].second;
		intersection::IntersectionData data;
		intersection::AABB aabb_a{
			body_a->get_hull().offset + body_a->get_transform().get_position(),
			body_a->get_hull().extends * 0.5f
		};
		intersection::AABB aabb_b{
			body_b->get_hull().offset + body_b->get_transform().get_position(),
			body_b->get_hull().extends * 0.5f
		};
		//if(body_a->get_collision_bodies()[0].collide_with(body_b->get_collision_bodies()[0], &data))
		if (intersection::intersect_aabb_aabb(aabb_a, aabb_b, &data)) {
			contacts.emplace_back(Contact{ collision_pairs[i], data.normal, data.penetration });
		}
	}


	// 3. Contact resolution
	for (auto contact : contacts)
	{
		resolve(std::move(contact), delta);
	}
}