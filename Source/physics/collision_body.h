#pragma once

#include "physics/aabb_hull.h"
#include "physics/intersection.h"

namespace physics
{
	class CollisionBody
	{
	public:
		AABBHull hull;

		bool collide_with(CollisionBody& collide_with, intersection::IntersectionData* data) const
		{
			//	intersection::AABB aabb_a{
			//	body_a->get_hull().offset + body_a->get_transform().get_position(),
			//body_a->get_hull().extends * 0.5f
			//};
			return true;
		}

		bool collide_with(intersection::Circle& collide_with, intersection::IntersectionData* data);
		bool collide_with(intersection::AABB& collide_with, intersection::IntersectionData* data);
		bool collide_with(intersection::Ray& collide_with, intersection::IntersectionData* data);
		bool collide_with(intersection::Polygon& collide_with, intersection::IntersectionData* data);
		bool collide_with(intersection::Ellipsoid& collide_with, intersection::IntersectionData* data);
		bool collide_with(intersection::Line& collide_with, intersection::IntersectionData* data);
	};
}
