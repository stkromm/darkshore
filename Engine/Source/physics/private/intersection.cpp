#include "intersection.h"

using namespace ds::physics::intersection;

bool intersect_aabb_aabb(AABB&& a, AABB&& b, IntersectionData* data)
{
	const ds::FVec2 difference = b.position - a.position;
	const ds::FVec2 full_extends_b = b.half_extends * 2;
	const ds::FVec2 full_extends_a = a.half_extends * 2;

	const bool hit =
		0 <= difference.x + full_extends_b.x && //
		difference.x <= full_extends_a.x && //
		0 <= difference.y + full_extends_b.y && //
		difference.y <= full_extends_a.y;

	if (hit && data)
	{
		const ds::FVec2 overlap = a.half_extends + b.half_extends - abs(difference);

		if (overlap.y < overlap.x)
		{
			if (difference.y < 0)
			{
				data->normal = { 0, -1 };
				data->penetration = { overlap.y };
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
				data->penetration = { overlap.x };
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

bool intersect_aabb_circle(AABB& box, Circle& circle, IntersectionData* data)
{
	ds::FVec2 relative_circle_pos = circle.position - box.position;
	const ds::FVec2 box_size = box.half_extends * 2;

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

	ds::FVec2 distance_vec = circle.position - (box.position + relative_circle_pos);
	const float distance = distance_vec.length();

	const bool hit = distance <= circle.radius;
	if (hit && data)
	{
		ds::FVec2 normal = (circle.position - box.position);
		normal.normalize();
		data->penetration = circle.radius - distance;
		data->normal = normal;
		data->point = relative_circle_pos + box.position;
	}
	return hit;
}

bool intersect_aabb_segment(AABB&& box, Line<float>&& line, IntersectionData* data)
{
	if (line.end.x < box.position.x)//If the second point of the segment is at left/bottom-left/top-left of the AABB
	{

	}
	else if (line.end.x > box.position.x + box.half_extends.x * 2) //If the second point of the segment is at right/bottom-right/top-right of the AABB
	{

	}
	else //If the second point of the segment is at top/bottom of the AABB
	{

	}
	return false;
}

//https://en.wikipedia.org/wiki/Line%E2%80%93line_intersection
template<typename T>
bool find_intersection(Line<T> a, Line<T> b, ds::Vec2<T>* intersection)
{
	const float denominator = (a.start.x - a.end.x)*(b.start.y - b.end.y) - (a.start.y - a.end.y)*(b.start.x - b.end.x);
	if (denominator == 0) return false;

	float x_nominator = 0;
	float y_nominator = 0;
	//float xNominator = (x1*y2 - y1 * x2)*(x3 - x4) - (x1 - x2)*(x3*y4 - y3 * x4);
	//float yNominator = (x1*y2 - y1 * x2)*(y3 - y4) - (y1 - y2)*(x3*y4 - y3 * x4);
	const float inverse_denominator = 1 / denominator;

	intersection = { x_nominator * inverse_denominator, y_nominator * inverse_denominator };
	return true;
}

template<typename T>
bool intersect_ray_line(ds::Vec2<T> origin, ds::Vec2<T> direction, ds::Vec2<T> line_a, ds::Vec2<T> line_b)
{
	T length_x = (line_a.x - origin.x) / direction.x;
	T ray_y_position = origin.y + direction.y * length_x;

	ds::Vec2<T> line_direction = line_b - line_a;
	if (line_direction * direction == ds::PI) // Lines are parallel. Check if ray contains line
	{
		if (ray_y_position == line_a.y)
		{
			return true; // Ray contains line
		}
		else
		{
			return false; // Ray is parallel to line
		}
	}
	else // Ray could intersect line
	{
		if (ray_y_position >= line_a.y && ray_y_position <= line_b.y)
		{
			T length_y = (line_a.y - origin.y) / direction.y;
			T ray_x_position = origin.x + direction.x * length_y;
			if (ray_x_position >= line_a.x && ray_x_position >= line_b.x)
			{
				return true;
			}
			return false;
		}
	}
	return false;
}