#include <gtest/gtest.h>
#include "../RayTracing/Geometry.h"

TEST(DotProduct, Zero)
{
	vector3d v1(0,0,0);
	vector3d v2(0,0,0);

	ASSERT_EQ(0, v1*v2);
}

TEST(DotProduct, Normal)
{
	vector3d v1(1,2,3);
	vector3d v2(4,5,6);

	ASSERT_EQ(32, v1*v2);
}