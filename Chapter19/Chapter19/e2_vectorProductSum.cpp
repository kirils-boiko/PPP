
/*	Exercise 2: template function that returns the sum of products of elements of one vector<T>
*	and another vector<U>;
*	For example, f(v1, v2) should do v1[i] += v2[i] for each element of v1;
*/

#include <vector>
#include <iostream>
#include <stdexcept>
#include <type_traits>
#include <iomanip>

class Size_error : public std::exception {
public:
	Size_error() :
		std::exception{ "inconsistent sizes of vectors" } {}
};

template<typename T, typename U> double sum_of_product(std::vector<T>& v1, std::vector<U>& v2)
{
	static_assert(std::is_arithmetic<T>::value, "type T must be numeric");
	static_assert(std::is_arithmetic<U>::value, "type U must be numeric");

	if (v1.size() != v2.size())
		throw Size_error{};

	double sum{ 0 };
	
	for (int i = 0; i < v1.size(); i++)
		sum += v1[i] * v2[i];
	return sum;
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
	std::vector<int> v2{ 2, 2, 2, 2, 2 };
	std::vector<double> v3{ 1.5, 1, 1, 1, 1 };
	std::vector<double> v4{ 1, 2, 3, 4, 5 };

	double sum = sum_of_product(v1, v3);

	print_vector(std::cout, v1);
	std::cout << std::endl;
	print_vector(std::cout, v2);
	std::cout << std::endl;
	std::cout << "The sum of products of elements of two vectors == " << 
		std::fixed << std::setprecision(2) << sum << std::endl;
}
catch (std::exception& e) {
	std::cerr << "error: " << e.what() << std::endl;
}
