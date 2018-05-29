#pragma once

#include "physics/rigid_body.h"

namespace physics
{
	struct Contact
	{
		Contact(std::pair<RigidBody*, RigidBody*> collision_pair, math::FVec2 normal, float penetration) : collision_pair(std::move(collision_pair)), normal(std::move(normal)),
		penetration(penetration) {}
		std::pair<RigidBody*, RigidBody*> collision_pair;
		math::FVec2 normal;
		float penetration;
		float friction = 1;
		float restituition = 1;
	};
}
