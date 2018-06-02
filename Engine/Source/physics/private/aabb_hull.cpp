#include "physics/aabb_hull.h"

#include <sstream>

using namespace ds::physics;

std::string AABBHull::to_string() const
{
	std::stringstream ss;
	ss << "AABBHull(Offset:" << offset.x << "," << offset.y << ";Extends:" << extends.x << "," << extends.y << ")";
	return ss.str();
}

void AABBHull::merge(AABBHull& hull)
{
	if (offset.x > hull.offset.x)
	{
		offset.x = hull.offset.x;
	}
	if (offset.x + extends.x < hull.offset.x + hull.extends.x)
	{
		extends.x = hull.offset.x + hull.extends.x - offset.x;
	}

	if (offset.y > hull.offset.y)
	{
		offset.y = hull.offset.y;
	}
	if (offset.y + extends.y < hull.offset.y + hull.extends.y)
	{
		extends.y = hull.offset.y + hull.extends.y - offset.y;
	}
}
