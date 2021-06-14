

/*	std::vector implementation Vector that does the range checking and prevents
*	the out of range access;
*/

#include <vector>
#include <iostream>
#include <stdexcept>	// for out_of_range

struct Range_error : std::out_of_range {	// enhanced vector range error reporting
	int index;
	Range_error(int i) : out_of_range{ "Range error" }, index(i) {}		// simple constructor
};

template<typename T> struct Vector: public std::vector<T> {
	using size_type = typename std::vector<T>::size_type;	// convenient synonym/alias for std::vector's size_type
	using vector<T>::vector;		// use vector<T>'s constructors

	T& operator[](size_type i)		// rather than return at(i);
	{
		if (i < 0 || i >= this->size()) throw Range_error{ i };
		return std::vector<T>::operator[](i);
	}

	const T& operator[](size_type i) const
	{
		if (i < 0 || i >= this->size()) throw Range_error{ i };
		return std::vector<T>::operator[](i);
	}
};