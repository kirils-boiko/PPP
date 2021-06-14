
#include <iostream>

/* 
	Illustrating the basic use of pointers;
	*/

int main()
{
	int x = 17;
	int* px = &x;			// pointer to int

	double e = 2.71828;
	double* pe = &e;		// pointer to double

	std::cout << "px dereferenced value is: " << *px << std::endl;
	std::cout << "while the address of value is: " << px << std::endl;

	std::cout << "pe dereferenced value is: " << *pe << std::endl;
	std::cout << "while the address of value is: " << pe << std::endl;
}

