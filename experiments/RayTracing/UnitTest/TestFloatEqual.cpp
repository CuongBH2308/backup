#include <gtest/gtest.h>
#include "../RayTracing/Geometry.h"

TEST(FloatEqual, Zero)
{
	ASSERT_TRUE(FloatEqual(0.0, 0.0));
	ASSERT_TRUE(FloatEqual(0.0, -0.0));
	ASSERT_TRUE(FloatEqual(-0.0, 0.0));
	ASSERT_TRUE(FloatEqual(-0.0, -0.0));
}

TEST(FloatEqual, Normal)
{
	ASSERT_TRUE(FloatEqual(1.0, 1.0));
	ASSERT_TRUE(FloatEqual(-1.0, -1.0));
}