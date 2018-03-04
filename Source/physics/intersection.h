#pragma once
#include <vector>

#include "rigid_body.h"
#include "math/vec2.h"
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
		/*
		bool intersect_aabb_aabb(const AABB& a, const AABB& b, IntersectionData* data = nullptr)
		{
			math::Vec2 difference = b.position - a.position;
			math::Vec2 full_extends_b = b.half_extends * 2;
			math::Vec2 full_extends_a = a.half_extends * 2;

			bool hit =
				0 <= difference.x + full_extends_b.x && //
				difference.x <= full_extends_a.x && //
				0 <= difference.y + full_extends_b.y && //
				difference.y <= full_extends_a.y;

			if (hit && data)
			{
				math::Vec2 overlap = a.half_extends + b.half_extends - abs(difference);

				if (overlap.y < overlap.x)
				{
					if (difference.y < 0)
					{
						data->normal = { 0,-1 };
						data->penetration = { -overlap.y };
					}
					else
					{
						data->normal = { 0, 1 };
						data->penetration = { overlap.y };
					}
				}
				else
				{
					if (difference.x < 0)
					{
						data->normal = { -1, 0 };
						data->penetration = { -overlap.x };
					}
					else
					{
						data->normal = { 1, 0 };
						data->penetration = { overlap.x };
					}
				}
			}
			return hit;
		}

		bool intersect_aabb_circle(const AABB& box, const Circle& circle, IntersectionData* data)
		{
			math::Vec2 relative_circle_pos = circle.position - box.position;
			math::Vec2 box_size = box.half_extends * 2;

			if (relative_circle_pos.x > box_size.x)
			{
				relative_circle_pos.x = box_size.x;
			}
			else if (relative_circle_pos.x < 0)
			{
				relative_circle_pos.x = 0;
			}
			if (relative_circle_pos.y > box_size.y)
			{
				relative_circle_pos.y = box_size.y;
			}
			else if (relative_circle_pos.y < 0)
			{
				relative_circle_pos.y = 0;
			}

			math::Vec2 distance_vec = circle.position - box.position - relative_circle_pos;
			float distance = 0;// length(distance_vec);

			bool hit = distance <= circle.radius;
			if (hit && data)
			{
				data->penetration = circle.radius - distance;
				data->normal = distance_vec;
				data->point = relative_circle_pos + box_size;
			}
			return hit;
		}*/
	};
};