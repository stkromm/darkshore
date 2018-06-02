#include "gtest/gtest.h"

#include "physics/private/intersection.h"

TEST(IntersectionTest, AabbAabbDontIntersect)
{
	physics::intersection::AABB a{
		{ 0,0 },{ 100,100 }
	};
	physics::intersection::AABB b{
		{ 500,500 },{ 100,100 }
	};

	EXPECT_FALSE(intersect_aabb_aabb(std::move(a), std::move(b), nullptr));
	a = {
		{ 0,0 },{ 100,100 }
	};
	b = {
		{ 500,500 },{ 100,100 }
	};
	physics::intersection::IntersectionData hit_data;
	EXPECT_FALSE(intersect_aabb_aabb(std::move(a), std::move(b), &hit_data));
}

TEST(IntersectionTest, AabbAabbShifted)
{
	physics::intersection::AABB a{
		{ 1.f,0.f },{ 100,100 }
	};
	physics::intersection::AABB b{
		{ 1.f,0.1f },{ 100,100 }
	};
	physics::intersection::IntersectionData hit_data;

	EXPECT_TRUE(intersect_aabb_aabb(std::move(a), std::move(b), &hit_data));
	EXPECT_EQ(hit_data.penetration, 199.9f);
	EXPECT_EQ(hit_data.point.x, 0.f);
	EXPECT_EQ(hit_data.point.y, 0.f);
	EXPECT_EQ(hit_data.normal.x, 0.f);
	EXPECT_EQ(hit_data.normal.y, 1.f);
}

TEST(IntersectionTest, AabbAabbContains)
{
	physics::intersection::AABB a{
		{ 0,0 },{ 100,100 }
	};
	physics::intersection::AABB b{
		{ 100,100 },{ 10,10 }
	};
	physics::intersection::IntersectionData hit_data;
	EXPECT_TRUE(intersect_aabb_aabb(std::move(a), std::move(b), &hit_data));
	EXPECT_EQ(hit_data.penetration, 10.0f);
	EXPECT_EQ(hit_data.point.x, 0.f);
	EXPECT_EQ(hit_data.point.y, 0.f);
	EXPECT_EQ(hit_data.normal.x, 1.f);
	EXPECT_EQ(hit_data.normal.y, 0.f);
}

TEST(IntersectionTest, AabbAabbIdentical)
{
	physics::intersection::AABB a{
		{0,0}, {100,100}
	};
	physics::intersection::AABB b{
		{ 0,0 },{ 100,100 }
	};
	physics::intersection::IntersectionData hit_data;

	EXPECT_TRUE(intersect_aabb_aabb(std::move(a), std::move(b), &hit_data));
	EXPECT_EQ(hit_data.penetration, 200.f);
	EXPECT_EQ(hit_data.point.x, 0.f);
	EXPECT_EQ(hit_data.point.y, 0.f);
	EXPECT_EQ(hit_data.normal.x, 1.f);
	EXPECT_EQ(hit_data.normal.y, 0.f);

	// Overlap on one axis
	// b only overlaps in positive y
	// b only overlaps in positive x
	// b only overlaps in negative y
	// b only overlaps in negative x

	// Overlap on two axis
	// b overlaps in positive y and x
	// b overlaps in negative y and x
	// b overlaps in positive y and negative x
	// b overlaps in negative y and positive x
}

TEST(IntersectionTest, CircleAabbIntersectCorner)
{
	physics::intersection::AABB aabb{
		{ 0,0 },{ 100,100 }
	};
	physics::intersection::Circle circle{
		{ 100,100 }, 100 
	};
	physics::intersection::IntersectionData hit_data;

	EXPECT_TRUE(physics::intersection::intersect_aabb_circle(aabb, circle, &hit_data));
	EXPECT_EQ(hit_data.penetration, 100.f);
	EXPECT_EQ(hit_data.point.x, 100.f);
	EXPECT_EQ(hit_data.point.y, 100.f);
	EXPECT_EQ(hit_data.normal.x, 0.707107f);
	EXPECT_EQ(hit_data.normal.y, 0.707107f);
}

int main()
{
	if (RUN_ALL_TESTS() != 0)
	{
	};
}