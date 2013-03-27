#include <gtest/gtest.h>
#include "../RayTracing/Geometry.h"

TEST(Intersection, XRay)
{
	ray r;
	r.origin = point3d(-1,0,0);
	r.direction = vector3d(1,0,0);

	triangle t;
	t.v0 = point3d(0,1,0);
	t.v1 = point3d(0,0,1);
	t.v2 = point3d(0,0,-1);

	point3d p;
	ASSERT_TRUE(RayTriangleIntersection(r,t,p));
	ASSERT_EQ(point3d(0,0,0), p);
}

TEST(Intersection, YRay)
{
	ray r;
	r.origin = point3d(0,-1,0);
	r.direction = vector3d(0,1,0);

	triangle t;
	t.v0 = point3d(0,0,1);
	t.v1 = point3d(-1,0,0);
	t.v2 = point3d(1,0,0);

	point3d p;
	ASSERT_TRUE(RayTriangleIntersection(r,t,p));
	ASSERT_EQ(point3d(0,0,0), p);
}

TEST(Intersection, ZRay)
{
	ray r;
	r.origin = point3d(0,0,-1);
	r.direction = vector3d(0,0,1);

	triangle t;
	t.v0 = point3d(0,1,0);
	t.v1 = point3d(-1,0,0);
	t.v2 = point3d(1,0,0);

	point3d p;
	ASSERT_TRUE(RayTriangleIntersection(r,t,p));
	ASSERT_EQ(point3d(0,0,0), p);
}