/*
	Illustrating the use of heap memory or free store
	using the keyword new;
	*/

#include <iostream>

class X {
	int my_int;
public:
	X();
	X(int i);
	void print() const;
};

class Y {
	int my_int;
public:
	Y(int i) : my_int{ i } {}
	void print() const { std::cout << my_int << std::endl; }
};

double* calc(int, int);

int main() {

	int n = 10;

	double* p = new double[4];	// allocate 4 doubles on the free store

	int* pi = new int;			// allocate one int
	int* qi = new int[4];		// allocate 4 ints (an array of 4 ints)

	double* pd = new double;	// allocate one double
	double* qd = new double[n];	// allocate n double (an array of n doubles)

	*p = 7.7;
	p[2] = 10.2;

	double x = *p;				// read the first object pointed to by p
	double y = p[2];			// read the 3rd object pointed to by p

	std::cout << "x == " << x << std::endl;
	std::cout << "y == " << y << std::endl;

	double* p0;					// uninitialized: likely trouble
	double* p1 = new double;	// get(allocate) an uninitialized double
	double* p2 = new double{ 5.5 };		// get a pointer to an initialized double
	double* p3 = new double[5];	// get(allocate) 5 uninitialized doubles;
	
	double* p4 = new double[5]{ 0,1,2,3,4 };	// array of objects allocated by new with the initializer list;
	double* p5 = new double[] {0, 1, 2, 3, 4};	// the number of elements can be left out since it is provided by the initializer list;

	X* px1 = new X;		// one default-initialized X
	X* px2 = new X[10];	// ten default-initialized X
	px1->print();

	Y* py1 = new Y { 10 };		// explicitly initialized since no default constructor
	py1->print();

	p0 = nullptr;	// the value zero is assigned to the pointer

	if (p0)
		std::cout << "p0 is not a nullptr" << std::endl;
	else
		std::cout << "p0 is a nullptr" << std::endl;

	double* r = calc(100, 1000);	// leaks memory

	double* r = calc_better(100, 1000);
	delete[] r;		// free the memory you're responsible for;

}

X::X() : my_int{ 0 } {}

X::X(int i) : my_int{ i } {}

void X::print() const { std::cout << my_int << std::endl; }


/* It is crucial to return memory to the free store after use
	to prevent memory leaks as in the following example */
double* calc(int res_size, int max) {		// leaks memory
	double* p = new double[max];
	double* res = new double[res_size];
	// ... use p to calculate results to be put in res
	return res;
}

/* Better version of calc() that prevents the memory leaks;
	the caller is still responsible for the memory allocated for res */
double* calc_better(int res_size, int max) {
	double* p = new double[max];
	double* res = new double[res_size];
	// ... use p to calculate result to be put in res
	delete[] p;		// we don't need that memory anymore: free it;
	return res;
}