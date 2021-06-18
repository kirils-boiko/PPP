
/*	Defining a class Int with a single member int;
	Constructors, assignment, operators +,-,*,/, <<, >> are defined
	*/

#include <iostream>
#include <stdexcept>

class Int {
private:
	int val;

public:

	Int()
		:val{ 0 } {}
	Int(int i)
		:val{ i } {}

	int value() { return val; }
	int value() const { return val; }
	
	Int(const Int&);				// copy constructor
	Int operator=(const Int&);		// copy assignment	

	Int operator+(const Int& i);	// overloading operator+ as member function
	Int operator-(const Int& i);	// overloading operator- as member function
	Int operator*(const Int& i);	// overloading operator* as member function
	Int operator/(const Int& i);	// overloading operator* as member function

	friend std::ostream& operator<<(std::ostream&, const Int& i);
	friend std::istream& operator>>(std::istream&, Int& i);

};

Int::Int(const Int& i)
	: val(i.val) {}

Int Int::operator=(const Int& i)
{
	val = i.value();
	return *this;
}

Int Int::operator+(const Int& i)
{
	return val + i.value();
}

Int Int::operator-(const Int& i)
{
	return val - i.value();
}

Int Int::operator*(const Int& i)
{
	return val * i.value();
}

Int Int::operator/(const Int& i)
{
	if (i.value() == 0)
		throw std::runtime_error("division by zero");
	return val / i.value();
}

std::ostream& operator<<(std::ostream& os, const Int& i)
{
	return os << i.val;
}

std::istream& operator>>(std::istream& is, Int& i)
{
	return is >> i.val;
}


int main()
try {
	Int i00;
	Int i01{ 10 };
	Int i02 = 100;
	Int i03 = i01;
	Int i04 = i01 + i02;
	Int i05;

	std::cout << "Enter an integer value: ";
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

}
catch (std::runtime_error& re) {
	std::cerr << "runtime error: " << re.what() << std::endl;
}