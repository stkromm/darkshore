#pragma once
#include <vector>

#include "core/math/vec2.h"

namespace physics
{
	namespace intersection
	{
		struct IntersectionData
		{
			math::FVec2 normal;
			math::FVec2 point;
			float penetration;
		};

		struct AABB
		{
			math::FVec2 position;
			math::FVec2 half_extends;
		};

		struct Circle
		{
			math::FVec2 position;
			float radius;
		};

		struct Ellipsoid
		{
			math::FVec2 position;
			float radius;
			float scale;
			float rotation;
		};

		struct OBB
		{
			math::FVec2 lower_left;
			math::FVec2 lower_right;
			math::FVec2 upper_right;
		};

		struct Polygon
		{
			std::vector<math::FVec2> points;
		};

		struct Line
		{
			math::FVec2 start;
			math::FVec2 end;
		};

		struct Ray
		{
			math::FVec2 origin;
			math::FVec2 direction;
		};

		bool intersect_aabb_aabb(const AABB& a, const AABB& b, IntersectionData* data = nullptr);

		bool intersect_aabb_circle(const AABB& box, const Circle& circle, IntersectionData* data);
	};
};
