#include "physics/physics.h"

#include <vector>
// ReSharper disable once CppUnusedIncludeDirective
#include <omp.h>
#include <algorithm>

#include "physics/private/contact-resolving.h"
#include "physics/private/intersection.h"
#include "physics/private/trace_datastructure.h"

using namespace ds::physics;

static std::vector<std::shared_ptr<RigidBody>> physic_bodies = {};
static TraceAccelerationDatastructure scene_graph;

bool ds::physics::init()
{
	physic_bodies = {};
	return true;
}

void ds::physics::shutdown()
{
	physic_bodies.clear();
}

void ds::physics::add_rigid_body(const std::shared_ptr<RigidBody> rigid_body)
{
	physic_bodies.push_back(rigid_body);
	scene_graph.add_rigid_body(rigid_body);
}

void ds::physics::tick(float delta)
{
	for (int iteration = 0; iteration < 2; ++iteration) {
		// Integration
#pragma omp parallel for schedule(dynamic)
		for (int i = 0; i < int(physic_bodies.size()); ++i)
		{
			physic_bodies[i]->integrate(delta);
		}

		scene_graph.build();

		// For large set of contacts
		// 1 : Build contact forest: nodes == rigidbodies, edge == contact between 2 rigidbodies
		// 2 : Remove edges in order to build even big (sub)trees.
		// 3 : Resolve trees in parallel
		// 4 : Resolve removed edges from 2

		// 3. Contact resolution
		for (auto contact : scene_graph.get_contacts())
		{
			resolve(std::move(contact));
		}
	}
}

