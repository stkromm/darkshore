#pragma once

#include <string>

#include "core/math/vec2.h"


namespace ds {
	namespace physics {
		struct AABBHull
		{
			/**
			Offset relative offset to transform position
			*/
			ds::FVec2 offset;
			/**
			Size of the AABB hull
			*/
			ds::FVec2 extends;

			std::string to_string() const;

			void merge(AABBHull& hull);
		};
	}
}