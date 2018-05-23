#pragma once

#include <string>

#include "core/math/vec2.h"

namespace physics
{
	struct AABBHull
	{
		/**
		Offset relative offset to transform position
		*/
		math::FVec2 offset;
		/**
		Size of the AABB hull
		*/
		math::FVec2 extends;

		std::string to_string() const;

		void merge(AABBHull& hull);
	};
}
