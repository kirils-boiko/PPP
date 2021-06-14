
/* 
	Illustrating the use of destructors;
	*/

#include <iostream>
#include <string>



/* 
	a very simplified vector of doubles;
	does a clean up using destructor;
	*/
class vector {
	int sz;				// the size
	double* elem;		// a pointer to elements
public:
	vector(int s)						// simple constructor
		:sz{ s }, elem{ new double[s] }
	{
		for (int i = 0; i < s; ++i) elem[i] = 0;	// initialize elems
	}
	
	int size() const { return sz; }		// current size
	
	~vector() { delete[] elem; }		// destructor to free memory
	// ...
};

void f3(int n) {
	double* p = new double[n];			// allocate n doubles
	vector v(n);						// the vector allocates n doubles
	// ... use p and v ...
	delete[] p;							// deallocate p's doubles
}	// vector automatically cleans up after v



/* 
	Illustrating the use of destructors and free store;
	*/
Shape* fct() {
	Text tt{ Point{200, 200}, "Annemarie" };
	// ...
	Shape* p = new Text{ Point{100,100}, "Nicholas" };
	return p;
}

void f() {
	Shape* q = fct();
	// ...
	delete q;
}