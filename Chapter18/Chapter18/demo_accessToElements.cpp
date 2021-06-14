
/*
*	Adding the usual subscript notation for accessing the elements of the vector;
*	This is done by defining a member function called operator[];
	*/

#include "myVector.h"
#include <iomanip>

// Naive addition of [] subscript operator
// Too simple, allows for reading but not writing since v[i] cannot be a LHS value
//	in assignment;
class vectorV1 : public vector {
public:
	// ... inherited from vector declared in myVector.h

	using vector::vector;		// inheriting all constructors

	double operator[](int n) { return elem[n]; }	// return element
};


// Second try: letting operator[] return a pointer to the appropriate element;
// Works but ugly like your mom;
class vectorV2 : public vector {
public:
	// ... inherited from vector declared in myVector.h

	using vector::vector;		// inheriting all constructors

	double* operator[](int n) { return &elem[n]; }	// return pointer
};


// Third try (conventional notation): to avoid dereferencing a pointer when writing to 
//	an element, use the reference instead of a pointer;
class vectorV3 : public vector {
public:
	// ... inherited from vector declared in myVector.h

	using vector::vector;		// inheriting all constructors

	double& operator[](int n) { return elem[n]; }
};

// Fourth try: adding a feature that allows to call operator[] on a const vector
//	to read from it;

class vectorV4 : public vector {
public:
	// ... inherited from vector declared in myVector.h

	using vector::vector;	// inheriting all constructors

	double& operator[](int n) { return elem[n]; }

	double operator[](int n) const { return elem[n]; }	// note: we cannot return a double&
};

int main()
{
	vectorV1 v1(10);
	std::cout << std::left << std::setw(8) << "v1" << ": ";
	double x = v1[2];
	//	v1[3] = x;	// error: left operand of = must be an l-value;
	std::cout << x << std::endl;

	vectorV2 v2(10);
	std::cout << std::left << std::setw(8) << "v2" << ": ";
	for (int i = 0; i < v2.size(); ++i) {	// ugly af
		*v2[i] = i;
		std::cout << *v2[i] << " ";
	}
	std::cout << std::endl;
	
	vectorV3 v3(10);
	std::cout << std::left << std::setw(8) << "v3" << ": ";
	for (int i = 0; i < v3.size(); ++i) {
		v3[i] = i;
		std::cout << v3[i] << " ";
	}
	std::cout << std::endl;

	vectorV4 v4(10);
	std::cout << std::left << std::setw(8) << "v4" << ": ";
	for (int i = 0; i < v4.size(); ++i) {
		v4[i] = i;
		std::cout << v4[i] << " ";
	}
	std::cout << std::endl;

	const vectorV4 v4_const(10);
	std::cout << std::left << std::setw(8) << "v4_const" << ": ";
	for (int i = 0; i < v4_const.size(); ++i) {
		//v4_const[i] = i;	// error: cannot assign to const
		std::cout << v4_const[i] << " ";
	}
	std::cout << std::endl;

}