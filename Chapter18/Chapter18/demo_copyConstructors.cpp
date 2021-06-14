
/*
*	Illustrating what it means to copy the vector by creating a copy constructor
*	for it;
*	Ideally, a copy vc of vector v should have:
*		vc.size() == v.size()
*		vc[i] == v[i] for all i in the range [0:v.size())
*	Note: also, the vector should return all memory to the free store upon the exit of 
*		its scope;
	*/



#include <initializer_list>
#include <algorithm>

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
		:sz{ lst.size() }, elem{ new double[sz] }	// uninitializer mem for elems
	{
		std::copy(lst.begin(), lst.end(), elem);			// initialize
	}

	vector(const vector&);							// copy constructor

	~vector() { delete[] elem; }

};

int main()
{
	vector v1 = { 1,2,3 };		// three elements 1.0, 2.0, 3.0
	vector v2{ 10, 20, 30 };	// three elements 10.0, 20.0, 30.0
	vector v3(3);				// three elements with the default value 0.0

	vector vc = v1;				// definition will initialize vc by a call of vector's copy constructor with v1 as its argument


}

vector::vector(const vector& arg)	// allocate elements, then initialize them by copying
	:sz{ arg.sz }, elem{ new double[arg.sz] }
{
	std::copy(arg.elem, arg.elem.sz, elem);
}
