
/*	Parameterizing classes with integer values;
	Stylized example that won't compile;
	*/

#include <iostream>
#include <vector>

template<typename T, int N> struct arr {
	T elem[N];				// hold elements in member array

	// rely on the default constructors, destructor, and assignment
	T& operator[] (int n);		// access: return reference
	const T& operator[] (int n) const;

	T* data() { return elem; }	// conversion to T*
	const T* data() const { return elem; }

	int size() const { return N; }
};

array<int, 256> gb;		// 256 integers
array<double, 6> ad = { 0.0, 1.1, 2.2, 3.3. 4.4, 5.5 };
constexpr int max = 1024;

void some_fct(int n)
{
	array<char, max> loc;	// OK: max is known at compile time
	array<char, n> oops;	// error: value of n not known to the compiler
	//...
	array<char, max> loc2 = loc;	// make backup copy
	//...
	loc = loc2;				// restore
	//...
}

template<typename C> void printout(const C& c)		// function template
{
	for (int i = 0; i < c.size(); ++i)
		std::cout << c[i] << std::endl;
}

int main()
{
	double* p = ad;			// error: no implicit conversion to pointer
	double* q = ad.data();	// OK: explicit conversion

	printout(ad);			// works with arrays cause of function template

	std::vector<int> vi;
	printout(vi);			// works with vectors too cause of function template
}

