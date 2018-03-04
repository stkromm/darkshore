#pragma once

#include "math\vec2.h"
#include "math\vec3.h"
#include "intersection.h"

namespace physics {
	struct Contact {
		std::pair<RigidBody, RigidBody>& collision_pair;

		CollisionBody& collider;
		CollisionBody& collided_width;
	};
}

