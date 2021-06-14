/*
*	If a vector has many elements, it can be expensive to copy it;
*	Therefore, we can 'steal' the representation of the original vector
*	without any copy by moving the original element pointer and element count
*	to the new vector;
*/

#include <initializer_list>
#include <algorithm>
#include <iostream>

class vector {
	int sz;			// the size
	double* elem;	// a pointer to the elements
public:
	vector(int s)	// constructor
		:sz{ s }, elem{ new double[s] }
	{
		for (int i = 0; i < s; i++)
			elem[i] = 0;
	}

	vector(std::initializer_list<double> lst)		// initializer-list constructor
		:sz{ static_cast<int>(lst.size()) }, elem{ new double[sz] }	// uninitializer mem for elems
	{
		std::copy(lst.begin(), lst.end(), elem);			// initialize
	}

	vector(const vector&);							// copy constructor

	vector& operator=(const vector&);				// copy assignment

	vector(vector&& arg);							// move constructor

	vector& operator=(vector&&);					// move assignment

	~vector() { delete[] elem; }

	void print();

	void push_back(double d) {}						// empty for now
};

vector fill(std::istream& is);

int main()
{
	vector v1 = { 1,2,3 };		// three elements 1.0, 2.0, 3.0
	vector v2{ 10, 20, 30 };	// three elements 10.0, 20.0, 30.0
	vector v3(3);				// three elements with the default value 0.0

	vector vc = v1;				// definition will initialize vc by a call of vector's copy constructor with v1 as its argument

	v3 = v2;					// copy assignment

	std::cout << "v1: ";
	v1.print();
	std::cout << std::endl;

	std::cout << "v1's copy: ";
	vc.print();
	std::cout << std::endl;

	std::cout << "v2: ";
	v2.print();
	std::cout << std::endl;

	std::cout << "v3 after copy assignment to v2: ";
	v3.print();
	std::cout << std::endl;

}

vector::vector(const vector& arg)	// copy constructor
// allocate elements, then initialize them by copying
	:sz{ arg.sz }, elem{ new double[arg.sz] }
{
	std::copy(arg.elem, arg.elem + arg.sz, elem);
}

vector& vector::operator=(const vector& arg)	// copy assignment
	// make this vector a copy of arg
	// operator= is regarded as a member function here, so it can directly
	//	refer to the members and use this pointer
{
	double* p = new double[arg.sz];				// allocate new space
	std::copy(arg.elem, arg.elem + arg.sz, p);		// copy elements
	delete[] elem;								// deallocate old space
	elem = p;									// reset to the newly allocated elements
	sz = arg.sz;
	return *this;								// return a self reference
}

vector::vector(vector&& arg)
	:sz{ arg.sz }, elem{ arg.elem }		// copy arg's elem pointer and size
{
	arg.sz = 0;
	arg.elem = nullptr;
}

vector& vector::operator=(vector&& arg)	// move arg to this vector
{
	delete[] elem;				// deallocate old space
	elem = arg.elem;
	sz = arg.sz;
	arg.elem = nullptr;
	arg.sz = 0;
	return *this;
}

void vector::print()
{
	std::cout << "{ ";
	for (int i = 0; i < sz; i++) std::cout << elem[i] << " ";
	std::cout << "}";
}

vector fill(std::istream& is)
{
	vector res;
	for (double x; is >> x; ) res.push_back(x);
	return res;
}