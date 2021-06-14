
/*
	Russkij Drill: Part2
	Understanding the use of pointers and their relation to arrays;
	*/

#include <iostream>
#include <string>
#include <cmath>

constexpr int N_ELEMENTS = 10;

class vector {
	int sz;							// the size
	double* elem;					// a pointer to the elements
public:
	vector(int s)						// simple constructor
		:sz{ s }, elem{ new double[s] }
	{
		for (int i = 0; i < s; ++i) elem[i] = 0;	// initialize elems
	}
	~vector() { delete[] elem; }		// destructor to free memory

	int size() const { return sz; }		// current size

	double get(int n) const { return elem[n]; }		// access: read
	void set(int n, double v) { elem[n] = v; }		// access: write
};

std::ostream& print_array(std::ostream& os, int* a, int n);
std::ostream& print_vector(std::ostream& os, vector& v);



int main()
{
	int i = 7;
	int* p1 = &i;

	std::cout << "Address of i:\t" << p1 << std::endl;
	std::cout << "Value of i:\t" << *p1 << std::endl;

	int* p2 = new int[N_ELEMENTS];
	for (int i = 0; i < N_ELEMENTS; i++)
		p2[i] = std::pow(2, i);

	std::cout << "Address of array:\t" << p2 << std::endl;
	print_array(std::cout, p2, N_ELEMENTS);
	std::cout << std::endl;

	int* p3 = p2;
	p2 = p1;
	p2 = p3;

	std::cout << "Value of p1 = " << p1 << " pointing to " << *p1 << std::endl;
	std::cout << "Value of p2 = " << p2 << " pointing to " << *p2 << std::endl;

	delete[] p2;

	p1 = new int[N_ELEMENTS];
	for (int i = 0; i < N_ELEMENTS; i++)
		p1[i] = std::pow(2, i);

	p2 = new int[N_ELEMENTS];

	for (int i = 0; i < N_ELEMENTS; i++)
		p2[i] = p1[i];

	std::cout << "Address of p1 array: " << p1 << std::endl;
	print_array(std::cout, p1, N_ELEMENTS);
	std::cout << std::endl;
	std::cout << "Address of p2 array: " << p2 << std::endl;
	print_array(std::cout, p2, N_ELEMENTS);
	std::cout << std::endl;

	delete[] p1;
	delete[] p2;


	// repeat 10-12 using a vector rather than an array;
	vector v1{ N_ELEMENTS };
	vector v2{ N_ELEMENTS };
	for (int i = 0; i < v1.size(); i++) {
		v1.set(i, pow(3, i));
		v2.set(i, v1.get(i));
	}
	
	std::cout << std::endl;
	std::cout << "Address of v1 vector: " << &v1 << std::endl;
	print_vector(std::cout, v1);
	std::cout << std::endl;
	std::cout << "Address of v2 vector: " << &v2 << std::endl;
	print_vector(std::cout, v2);
	std::cout << std::endl;


	
}


std::ostream& print_array(std::ostream& os, int* a, int n)	// prints the n values to os
{
	os << "{ ";
	while (n-- > 0)
		os << *a++ << " ";
	return os << "}";
}

std::ostream& print_vector(std::ostream& os, vector& v)
{
	os << "{ ";
	for (int i = 0; i < v.size(); i++)
		os << v.get(i) << " ";
	return os << "}";
}