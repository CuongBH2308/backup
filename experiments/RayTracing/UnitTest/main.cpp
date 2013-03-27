#include <iostream>

#include <gtest/gtest.h>

int main(int argc, char **argv) {
	std::cout << "Running main() from gtest_main.cc\n";

	testing::InitGoogleTest(&argc, argv);
	int ret = RUN_ALL_TESTS();

	scanf("%i", ret);
	return ret;
}