#pragma once

#include "physics/rigid_body.h"

namespace physics
{
	struct Contact
	{
		std::pair<RigidBody*, RigidBody*> collision_pair;
		math::FVec2 normal;
		float penetration;
		float friction = 1;
		float restituition = 1;
	};
}
