
/*
	For vector to be usable, get() and set() provide a way to read
	and write elements
	*/

#include <iostream>
#include <string>

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

int main() {
	vector v(10);
	for (int i = 0; i < v.size(); ++i) {
		v.set(i, 1.1 * i);
		std::cout << "v[" << i << "]==" << v.get(i) << std::endl;
	}
}