
/*	Exercise 1: template function that adds the elements of one vector<T>
*	to the elements of another;
*	For example, f(v1, v2) should do v1[i] += v2[i] for each element of v1;
*/

#include <vector>
#include <iostream>
#include <stdexcept>

class Size_error : public std::exception {
public:
	Size_error() :
		std::exception{ "inconsistent sizes of vectors" } {}
};


template<typename T> void f(std::vector<T>& v1, std::vector<T>& v2)
{
	if (v1.size() != v2.size())
		throw Size_error{};
	for (int i = 0; i < v1.size(); i++)
		v1[i] += v2[i];
	return;
}

template<typename T> std::ostream& print_vector(std::ostream& os, const std::vector<T>& v)
{
	os << "{ ";
	for (int i = 0; i < v.size(); i++)
		os << v[i] << ' ';
	return os << '}';
}

int main()
try {
	std::vector<int> v1{ 10, 20, 30, 40, 50 };
	std::vector<int> v2{ 1, 1, 1, 1, 1 };
	std::vector<int> v3{ 1, 1, 1, 1, 1, 1 };

	f(v1, v2);

	print_vector(std::cout, v1);
	std::cout << std::endl;

	f(v1, v3);
}
catch (std::exception& e) {
	std::cerr << "error: " << e.what() << std::endl;
}
