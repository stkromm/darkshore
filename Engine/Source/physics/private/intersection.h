#pragma once
#include <vector>

#include "core/math/vec2.h"

namespace ds {
	namespace physics
	{
		namespace intersection
		{
			struct IntersectionData
			{
				ds::FVec2 normal;
				ds::FVec2 point;
				float penetration;
			};

			struct AABB
			{
				ds::FVec2 position;
				ds::FVec2 half_extends;
			};

			struct Circle
			{
				ds::FVec2 position;
				float radius;
			};

			struct Ellipsoid
			{
				ds::FVec2 position;
				float radius;
				float scale;
				float rotation;
			};

			struct OBB
			{
				ds::FVec2 lower_left;
				ds::FVec2 lower_right;
				ds::FVec2 upper_right;
			};

			struct Polygon
			{
				std::vector<ds::FVec2> points;
			};

			template<typename T>
			struct Line
			{
				ds::Vec2<T> start;
				ds::Vec2<T> end;
			};

			template<typename T>
			struct Ray
			{
				ds::Vec2<T> origin;
				ds::Vec2<T> direction;
			};

			bool intersect_aabb_aabb(AABB&& a, AABB&& b, IntersectionData* data = nullptr);

			bool intersect_aabb_circle(AABB& box, Circle& circle, IntersectionData* data = nullptr);

			bool intersect_aabb_segment(AABB&& box, Line<float>&& line, IntersectionData* data = nullptr);
		}
	}
}