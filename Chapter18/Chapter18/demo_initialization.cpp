
/* 
	Illustrating the efficient way of initializing
	the vector with a set of values instead of
	initializing it with the defaults and then
	assigning the values;
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

	~vector(){ delete[] elem; }

};

int main()
{
	vector v1 = { 1,2,3 };		// three elements 1.0, 2.0, 3.0
	vector v2{ 10, 20, 30 };	// three elements 10.0, 20.0, 30.0
	vector v3(3);				// three elements with the default value 0.0
	
}