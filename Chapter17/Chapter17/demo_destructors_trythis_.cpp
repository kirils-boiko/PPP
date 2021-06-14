
/* 
	Program illustrating the use of constructors and destructors;
	It uses base classes and members where the constructors and
	destructors output a line of info when they are called;
	*/

#include <iostream>
#include <string>



class Base {
public:
	Base() {
		std::cout << "Constructing the Base" << std::endl;
	}
	virtual ~Base() {
		std::cout << "Destructing the Base" << std::endl;
	}
};

class Derived : public Base {
public:
	Derived() {
		std::cout << "Constructing the Derived" << std::endl;
	}

	~Derived() {
		std::cout << "Destructing the Derived" << std::endl;
	}

};


int main() {


	Base* pbd  = new Derived;
	std::cout << "Pause" << std::endl;
	delete pbd;

	std::cout << std::endl;
	
	Derived* pd = new Derived;
	std::cout << "Pause" << std::endl;
	delete pd;
}