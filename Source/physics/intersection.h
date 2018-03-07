#pragma once
#include <vector>

#include "core/math/vec2.h"

namespace physics
{
	namespace intersection
	{
		struct IntersectionData
		{
			math::Vec2 normal;
			math::Vec2 point;
			float penetration;
		};

		struct AABB
		{
			math::Vec2 position;
			math::Vec2 half_extends;
		};

		struct Circle
		{
			math::Vec2 position;
			float radius;
		};

		struct Ellipsoid
		{
			math::Vec2 position;
			float radius;
			float scale;
			float rotation;
		};

		struct OBB
		{
			math::Vec2 lower_left;
			math::Vec2 lower_right;
			math::Vec2 upper_right;
		};

		struct Polygon
		{
			std::vector<math::Vec2> points;
		};

		struct Line
		{
			math::Vec2 start;
			math::Vec2 end;
		};

		struct Ray
		{
			math::Vec2 origin;
			math::Vec2 direction;
		};
		
		bool intersect_aabb_aabb(const AABB& a, const AABB& b, IntersectionData* data = nullptr);

		bool intersect_aabb_circle(const AABB& box, const Circle& circle, IntersectionData* data);
	};
};