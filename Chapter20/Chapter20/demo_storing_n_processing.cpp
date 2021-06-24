
/*	The fundamental problem: we don't control the way in which our "data suppliers" store the data
*	so we have to work with the data in the form in which it is given or read it and store it the way
*	we prefer;
*/

#include <iostream>
#include <vector>

double* get_from_jack(int* count);		// Jack puts double into an array and return the num of elements in *count
std::vector<double*> get_from_jill();	// Jill fills the std::vector

void fct()
	// assuming that the data is stored on the heap and we should manage it;
	// assuming that we can't rewrite Jack's or Jill's code;
{
	int jack_count = 0;
	double* jack_data = get_from_jack(&jack_count);

	std::vector<double>* jill_data = get_from_jill();
	// ... process ...
	delete[] jack_data;
	delete jill_data;
}


//-----------------------------------------------------
// Find the element with the highest value in each set
// Done by inserting this piece of code into ... process ... part of fct()
{
	double h = -1;
	double* jack_high;	// points to the element with the highest value
	double* jill_high;	// points to the element with the highest value

	for (int i = 0; i < jack_count; ++i)
		if (h < jack_data[i]) {
			jack_high = &jack_data[i];		// save the address of the largest element
			h = jack_data[i];				// update the largest element
		}

	h = -1;
	for (int i = 0; i < jill_data->size(); ++i)
		if (h < (*jill_data)[i]) {
			jill_high = &(*jill_data)[i];	// save the address of the largest element
			h = (*jill_data)[i];			// update the largest element
		}

	std::cout << "Jack's max: " << *jack_high << std::endl;
	std::cout << "Jill's max: " << *jill_high << std::endl;
}

// Note: to get rid of (*jill_data)[i] ugliness we could use a move constructor when
//	to return a vector or return a vector reference from  get_from_jill() rather than a vector*


//-----------------------------------------------------
// Generalizing code: uniform way of accessing and manipulating data

// Introducing a vector reference for the convenient use of Jill's data
{
	std::vector<double>& v = *jill_data;
	for (int i = 0; i < v.size(); ++i)
		if (h < v[i]) {
			jill_high = &v[i];
			h = v[i];
		}
}

// General solution based on pointers
double* high(double* first, double* last)
// return a pointer to the element in [first, last) that has the highest value
{
	double h = -1;
	double* high;
	for (double* p = first, p != last; ++p)
		if (h < *p) {
			high = p;
			h = *p;
		}
	return high;
}

// Given the general solution, finding the largest element is trivial
{
	double* jack_high = high(jack_data, jack_data + jack_count);
	std::vector<double>& v = *jill_data;
	double* jill_high = high(&v[0], &v[0] + v.size());

	std::cout << "Jack's max: " << *jack_high << std::endl;
	std::cout << "Jill's max: " << *jill_high << std::endl;
}

// Notes: 
//	solution works for arrays only (incl. vectors);
//	can be used only for arrays of doubles, not other types;
//	can also find the highest element in part of array;