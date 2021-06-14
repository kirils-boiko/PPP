
/* 
	Illustrating the use of unary sizeof() operator
	*/

#include <iostream>

void sizes(char, int, int*, bool, double, double*);


int main() {
	char ch = 'a';
	int i = 1000;
	int* pi = &i;
	double d = 2000.00;
	double* pd = &d;
	bool b = true;

	sizes(ch, i, pi, b, d, pd);
}

void sizes(char ch, int i, int* pi, bool b, double d, double* pd) {
	std::cout << "the size of char is " << sizeof(char) << " "
		<< sizeof(ch) << std::endl;
	std::cout << "the size of int is " << sizeof(int) << " "
		<< sizeof(i) << std::endl;
	std::cout << "the size of ptr to int is " << sizeof(int*) << " "
		<< sizeof(pi) << std::endl;
	std::cout << "the size of bool is " << sizeof(bool) << " "
		<< sizeof(b) << std::endl;
	std::cout << "the size of double is " << sizeof(double) << " "
		<< sizeof(d) << std::endl;
	std::cout << "the size of ptr to double is " << sizeof(double*) <<
		" " << sizeof(pd) << std::endl;
}