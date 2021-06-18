 
/*	Tracer class whose constructor prints a string and its destructor prints a strings
*	passed as the arguments in the constructor;
*	The class is used to demonstrate the RAII management of local objects, member objects,
*	global objects, and objects allocated on heap using new;
*/

#include <iostream>
#include <string>
#include <memory>

class Tracer {
	std::string constructor_str;
	std::string destructor_str;

public:
	Tracer(std::string s1 = "empty string", std::string s2 = "empty string")
		: constructor_str{ s1 }, destructor_str{ s2 }
	{
		std::cerr << this << ": " << constructor_str << std::endl;
	}

	Tracer(const Tracer& arg)
		: constructor_str{ arg.constructor_str }, destructor_str{ arg.destructor_str }
	{
		std::cerr << this << ": copy constructor is invoked using " << &arg << std::endl;
	}

	Tracer& operator=(const Tracer& arg)
	{
		constructor_str = arg.constructor_str;
		destructor_str = arg.destructor_str;
		std::cerr << this << ": copy assignment is invoked using " << &arg << std::endl;
		return *this;
	}

	~Tracer() { std::cerr << this << ": " << destructor_str << std::endl; }

	
};

class Test {
	Tracer m_obj;

public:
	Test(std::string s1 = "empty string", std::string s2 = "empty string")
		:m_obj{ s1, s2 } {}
};

Tracer g_obj{ "global object is constructed", "global object is destroyed" };

int main()
{
	Tracer l_obj{ "local object is constructed", "local object is destroyed" };
	Test m_obj{ "member object is constructed", "member object is destroyed" };
	Tracer* h_obj = new Tracer{ "heap object is constructed", "heap object is destroyed" };

	Tracer c_obj{ l_obj };
	delete h_obj;
}