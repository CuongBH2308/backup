#include <gtest/gtest.h>
#include "../RayTracing/Geometry.h"

TEST(CrossProduct, Simple)
{
	vector3d X(1, 0, 0);
	vector3d Y(0, 1, 0);

	vector3d Z = X ^ Y;
	ASSERT_EQ(vector3d(0, 0, 1), Z);
}