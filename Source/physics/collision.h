#pragma once

#include "math\vec2.h"
#include "math\vec3.h"

namespace physics {
	struct Rectangle {
		math::Vec2 center;
		math::Vec2 half_extends;
	};

	struct Circle {
		math::Vec2 center;
		float radius;
	};

	struct Box {
		math::Vec3 center;
		math::Vec3 half_extends;
	};

	struct Sphere {
		math::Vec3 center;
		float radius;
	};
}

