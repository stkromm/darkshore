#include "physics/intersection.h"

bool physics::intersection::intersect_aabb_aabb(const AABB& a, const AABB& b, IntersectionData* data)
{
	const math::Vec2 difference = b.position - a.position;
	const math::Vec2 full_extends_b = b.half_extends * 2;
	const math::Vec2 full_extends_a = a.half_extends * 2;

	const bool hit =
		0 <= difference.x + full_extends_b.x && //
		difference.x <= full_extends_a.x && //
		0 <= difference.y + full_extends_b.y && //
		difference.y <= full_extends_a.y;

	if (hit && data)
	{
		const math::Vec2 overlap = a.half_extends + b.half_extends - abs(difference);

		if (overlap.y < overlap.x)
		{
			if (difference.y < 0)
			{
				data->normal = {0, -1};
				data->penetration = {overlap.y};
			}
			else
			{
				data->normal = {0, 1};
				data->penetration = {overlap.y};
			}
		}
		else
		{
			if (difference.x < 0)
			{
				data->normal = {-1, 0};
				data->penetration = {overlap.x};
			}
			else
			{
				data->normal = {1, 0};
				data->penetration = {overlap.x};
			}
		}
	}
	return hit;
}

bool physics::intersection::intersect_aabb_circle(const AABB& box, const Circle& circle, IntersectionData* data)
{
	math::Vec2 relative_circle_pos = circle.position - box.position;
	const math::Vec2 box_size = box.half_extends * 2;

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
	const float distance = distance_vec.length();

	const bool hit = distance <= circle.radius;
	if (hit && data)
	{
		data->penetration = circle.radius - distance;
		data->normal = distance_vec;
		data->point = relative_circle_pos + box_size;
	}
	return hit;
}
