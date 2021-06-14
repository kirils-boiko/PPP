
/*
*	Illustrating the times of construction and destruction using print statements;
	*/

#include <iostream>
#include <string>
#include <vector>

struct X {	// simple test class
	int val;

	void out(const std::string& s, int nv)
	{
	std::cerr << this << "->" << s << ": from " << val << " to " << nv << std::endl;
	}

	X() { out("X()", 0); val = 0; }				// default constructor
	X(int v) { out("X(int)", v); val = v; }
	X(const X& arg) { out("X(X&) ", arg.val); val = arg.val; }	// copy constructor
	X& operator=(const X& arg) { out("X::operator=()", arg.val); val = arg.val; return *this; } //copy assignment
	~X() { out("~X()", 0); }					// destructor
};

X glob(2);			// global variable

X copy(X a) { return a; }

X copy2(X a) { X aa = a; return aa; }

X& ref_to(X& a) { return a; }

X* make(int i) { X a(i); return new X(a); }

struct XX { X a; X b; };

int main()
{
	X loc_def;			// local default variable
	std::cout << std::endl;
	X loc{ 4 };			// local variable
	std::cout << std::endl;
	X loc2{ loc };		// copy construction
	std::cout << std::endl;
	loc = X{ 5 };		// copy assignment
	std::cout << std::endl;
	loc2 = copy(loc);	// copy assignment: call by value and return
	std::cout << std::endl;
	X loc3{ 6 };		// another local variable
	std::cout << std::endl;
	X& r = ref_to(loc);	// call by reference and return
	std::cout << std::endl;
	delete make(7);		// allocating on free store using the copy constructor and destroying
	std::cout << std::endl;
	delete make(8);
	std::cout << std::endl;
	std::vector <X> v(4);	// default values
	std::cout << std::endl;
	XX loc4;				// XX object with two Xs with default values
	std::cout << std::endl;
	X* p = new X{ 9 };		// an X on the free store
	std::cout << std::endl;
	delete p;				// calling the destructor
	std::cout << std::endl;
	X* pp1 = new X[5];		// an array of Xs on the free store
	std::cout << std::endl;
	delete[] pp1;			// destroying the array;
	std::cout << std::endl;
	X* pp2 = new X[5] {1, 2, 3, 4, 5 };		// an array of Xs on the free store
	std::cout << std::endl;
	delete[] pp2;			// destroying the array;
	std::cout << std::endl;
}