
/*
	Russkij Drill: Part1
	Understanding the use of free-store-allocated arrays and contrasting
	arrays with vectors;
	*/

#include <iostream>
#include <string>

constexpr int N_ELEMENTS = 11;

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


std::ostream& print_array(std::ostream& os, int* a, int n);	// prints n values to os
std::ostream& print_vector(std::ostream& os, vector& v);


int main()
{
	int* p = new int[N_ELEMENTS];
	std::cout << "{ ";
	for (int i = 0; i < N_ELEMENTS; i++) {
		*(p+i) = 100 + i;
		std::cout << *(p+i) << " ";
	}
	std::cout << "}" << std::endl;

	print_array(std::cout, p, N_ELEMENTS);
	std::cout << std::endl;	
	delete[] p;

	vector v{ N_ELEMENTS };
	for (int i = 0; i < v.size(); i++)
		v.set(i, 100 + i);
	print_vector(std::cout, v);
	std::cout << std::endl;

	return 0;
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