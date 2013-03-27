#include <gtest/gtest.h>
#include "../RayTracing/Geometry.h"
#include "../RayTracing/Octree.h"

TEST(RayIntersectWithCube, XAxis)
{
	ray r;
	r.origin = point3d(-5, 0, 0);
	r.direction = vector3d(1, 0, 0);

	cube c;
	c.center = point3d(0,0,0);
	c.halfsize = 2;

	ASSERT_TRUE(RayIntersectWithCube(r, c));
}

TEST(RayIntersectWithCube, YAxis)
{
	ray r;
	r.origin = point3d(0, -5, 0);
	r.direction = vector3d(0, 1, 0);

	cube c;
	c.center = point3d(0,0,0);
	c.halfsize = 2;

	ASSERT_TRUE(RayIntersectWithCube(r, c));
}

TEST(RayIntersectWithCube, ZAxis)
{
	ray r;
	r.origin = point3d(0, 0, -5);
	r.direction = vector3d(0, 0, 1);

	cube c;
	c.center = point3d(0,0,0);
	c.halfsize = 2;

	ASSERT_TRUE(RayIntersectWithCube(r, c));
}

TEST(RayIntersectWithCube, InCube)
{
	ray r;
	r.origin = point3d(0, 0, 0);
	r.direction = vector3d(2, -5, 1);
	Normalize(r.direction);

	cube c;
	c.center = point3d(0,0,0);
	c.halfsize = 2;

	ASSERT_TRUE(RayIntersectWithCube(r, c));
}

TEST(RayIntersectWithCube, Normal)
{
	ray r;
	r.origin = point3d(108.41000, 115.67300, 75.917000);
	r.direction = vector3d(-0.64967400, -0.65163702, -0.39152700);
	Normalize(r.direction);

	cube c;
	c.center = point3d(15.872475,15.872475,5.2908249);
	c.halfsize = 5.2908249;

	ASSERT_TRUE(RayIntersectWithCube(r, c));
}
