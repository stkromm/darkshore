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

		template<typename T>
		struct Line
		{
			math::Vec2<T> start;
			math::Vec2<T> end;
		};

		template<typename T>
		struct Ray
		{
			math::Vec2<T> origin;
			math::Vec2<T> direction;
		};

		bool intersect_aabb_aabb(AABB&& a, AABB&& b, IntersectionData* data = nullptr);

		bool intersect_aabb_circle(AABB& box, Circle& circle, IntersectionData* data = nullptr);

		bool intersect_aabb_segment(AABB&& box, Line<float>&& line, IntersectionData* data = nullptr);
	};
};
