#include <foo.h>
#include <iostream>

int main()
{
	foo();
	std::cout << "bar" << std::endl;
	
	// hang the process so we can check it
	int tmp;
	std::cin >> tmp;
}