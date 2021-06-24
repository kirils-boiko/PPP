
/*	Expressin the "find the element with the largest value" problem using
*	the STL notion of a sequence;
*/

#include <vector>
#include <iostream>
#include <stdexcept>

class Range_error : public std::out_of_range {

public:
	Range_error(std::string s) : std::out_of_range{ s } {}
};

template <typename Iterator>
Iterator high(Iterator first, Iterator last)
// return an iterator to the element in [first:last) that has the highest value
{
	if (last <= first)
		throw Range_error{ "Iterator range error" };
	Iterator high = first;
	for (Iterator p = first; p != last; ++p)
		if (*high < *p) high = p;
	return high;
}

double* get_from_jack(int* count);		// Jack puts double into an array and returns the numb of elems in *count
std::vector<double>* get_from_jill();	// Jill fills the vector

void fct()
{
	int jack_count = 0;
	double* jack_data = get_from_jack(&jack_count);
	std::vector<double>* jill_data = get_from_jill();

	double* jack_high = high(jack_data, jack_data + jack_count);
	std::vector<double>& v = *jill_data;
	double* jill_high = high(&v[0], &v[0] + v.size());

	std::cout << "Jack's high: " << *jack_high << std::endl;
	std::cout << "Jill's high: " << *jill_high << std::endl;

	delete[] jack_data;
	delete jill_data;
}

double* get_from_jack(int* count)
	// arbitrary data for testing
{
	double* p = new double[10];
	for (int i = 0; i < 10; i++) {
		*(p + i) = 10 - i;
	}
	*count = 10;
	return p;
}

std::vector<double>* get_from_jill()
	// arbitrary data for testing
{
	std::vector<double>* p = new std::vector<double>;
	for (int i = 0; i < 10; i++)
		p->push_back(i * i);
	return p;
}

int main()
try {
	fct();
}
catch (std::out_of_range& e) {
	std::cerr << e.what() << std::endl;
}