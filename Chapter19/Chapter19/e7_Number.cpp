
/*	Defining a template class Number<T> with a single numeric member T;
	Constructors, assignment, operators +,-,*,/, %, <<, >> are defined
	Tested on the solution to the Exercise 2: sum of products;
	The solution is not robust to passing the vectors of non-numeric types
	into the sum_of_product types;
	Making it robust would require the user-defined traits to check
	for the "customer numeric" types and is beyond the scope of this exercise;
	*/

#include <vector>
#include <iostream>
#include <stdexcept>
#include <type_traits>
#include <cmath>

template<typename T>
class Number;	// forward declaration to make function template declaration possible

class Size_error : public std::exception {
public:
	Size_error() :
		std::exception{ "inconsistent sizes of vectors" } {}
};

template<typename T, typename U> double sum_of_product(std::vector<T>& v1, std::vector<U>& v2)
{
	if (v1.size() != v2.size())
		throw Size_error{};

	double sum{ 0 };

	for (int i = 0; i < v1.size(); i++)
		sum = sum + double(v1[i]) * double(v2[i]);
	return sum;
}


template<typename T> std::ostream& print_vector(std::ostream& os, const std::vector<T>& v)
{
	os << "{ ";
	for (int i = 0; i < v.size(); i++)
		os << v[i] << ' ';
	return os << '}';
}


template<typename T>
std::ostream& operator<<(std::ostream&, const Number<T>&);	// forward declaration of template operator overloading so that you can define it further outside of the class body;

template<typename T>
std::istream& operator>>(std::istream&, Number<T>&);	// forward declaration

template<typename T>
class Number {
	static_assert(std::is_arithmetic<T>::value, "T must be numeric");

private:
	T val;

public:

	Number(T n = 0)
		:val{ n } {}

	T value() { return val; }
	T value() const { return val; }

	Number(const Number&);				// copy constructor
	Number operator=(const Number&);	// copy assignment	

	operator double() const { return val; }

	Number operator+(const Number&);	// overloading operator+ as member function
	Number operator-(const Number&);	// overloading operator- as member function
	Number operator*(const Number&);	// overloading operator* as member function
	Number operator/(const Number&);	// overloading operator* as member function
	Number operator%(const Number&);

	friend std::ostream& operator<< <T>(std::ostream&, const Number&);
	friend std::istream& operator>> <T>(std::istream&, Number&);

};

template<typename T>
Number<T>::Number(const Number<T>& i)
	: val(i.val) {}

template<typename T>
Number<T> Number<T>::operator=(const Number<T>& n)
{
	val = n.value();
	return *this;
}

template<typename T>
Number<T> Number<T>::operator+(const Number<T>& n)
{
	return Number<T>{ val + n.value() };
}

template<typename T>
Number<T> Number<T>::operator-(const Number<T>& n)
{
	return Number<T>{ val - n.value() };
}

template<typename T>
Number<T> Number<T>::operator*(const Number<T>& n)
{
	return Number<T>{ val* n.value() };
}

template<typename T>
Number<T> Number<T>::operator/(const Number<T>& n)
{
	if (n.value() == 0)
		throw std::runtime_error("division by zero");
	return Number<T>{ val / n.value() };
}

template<typename T>
Number<T> Number<T>::operator%(const Number<T>& n)
// works for integer and floating-point types
{
	if (n.value() == 0)
		throw std::runtime_error("division by zero");
	T sign = (val < 0) ? -1 : 1;
	T dividend = (val < 0) ? -val : val;					// absolute value
	T divisor = (n.value() < 0) ? -n.value() : n.value();	// absolute value

	while (dividend >= divisor)
		dividend = dividend - divisor;
	return Number<T>{ dividend* sign };

}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Number<T>& n)
{
	return os << n.val;
}

template<typename T>
std::istream& operator>>(std::istream& is, Number<T>& n)
{
	return is >> n.val;
}


int main()
try {

	//-----------------------------------------------------------------//
	// Testing exercise 6

	Number<int> i00;
	Number<int> i01{ 10 };
	Number<int> i02 = 100;
	Number<int> i03 = i01;
	Number<int> i04 = i01 + i02;
	Number<int> i05;
	Number<double> dividend = -5;
	Number<double> divisor = 2;

	std::cout << "Enter a numeric value: ";
	std::cin >> i05;

	std::cout << "i00 == " << i00 << std::endl;
	std::cout << "i01 == " << i01 << std::endl;
	std::cout << "i02 == " << i02 << std::endl;
	std::cout << "i03 == " << i03 << std::endl;
	std::cout << "i04 == " << i04 << std::endl;
	std::cout << "i05 == " << i05 << std::endl;

	std::cout << i02 + i01 << std::endl;
	std::cout << i02 - i01 << std::endl;
	std::cout << i02 * i01 << std::endl;
	std::cout << i02 / i01 << std::endl;
	std::cout << dividend % divisor << std::endl;

	//-----------------------------------------------------------------//
	// Testing exercise 7

	std::vector<Number<int>> v00{ 1, 2, 3, 4, 5 };
	std::vector<Number<int>> v01{ 1, 1, 1, 1, 1 };

	double sum = sum_of_product(v00, v01);

	print_vector(std::cout, v00); 
	std::cout << std::endl;
	print_vector(std::cout, v01);
	std::cout << std::endl;
	std::cout << "The sum of products of elements of two vectors == " << sum << std::endl;

}
catch (std::runtime_error& re) {
	std::cerr << "runtime error: " << re.what() << std::endl;
}
catch (std::exception& e) {
	std::cerr << "error: " << e.what() << std::endl;
}