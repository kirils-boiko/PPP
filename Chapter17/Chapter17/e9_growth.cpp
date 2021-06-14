
/*
	Program that determines whether the stack and heap memeory grow
	upwards (towards higher addresses) or downwards (towards lower addresses)
	*/

#include <iostream>

int main()
{
	int a = 0, b = 0, c = 0;	// stack

	std::cout << &a << " " << &b << " " << &c << std::endl;
	std::cout << "difference between a and b addresses: " << &a - &b << std::endl;
	std::cout << "difference between b and c addresses: " << &b - &c << std::endl;
	if (&a > &b)
		std::cout << "The stack memory grows downwards" << std::endl;
	else
		std::cout << "The stack memory grows upwards" << std::endl;

	int* d = new int;
	int* e = new int;

	std::cout << d << " " << e << std::endl;
	std::cout << "difference between d and e pointers: " << d - e << std::endl;
	if (d > e)
		std::cout << "The heap memory grows downwards" << std::endl;
	else
		std::cout << "The heap memory grows upwards" << std::endl;


	delete d;
	delete e;
}