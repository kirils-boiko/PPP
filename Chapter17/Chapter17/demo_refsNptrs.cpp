
/* 
	Illustrating the differences between references and pointers;
	*/

#include <iostream>

class Base {
public:
	int i = 0;
	Base() { std::cout << "Base is constructed\n"; }
	virtual ~Base() { std::cout << "Base is destructed\n"; }
};

class Derived : public Base {
public:
	Derived() { std::cout << "Derived is constructed\n"; }
	~Derived() { std::cout << "Derived is destructed\n"; }
};

void increment(Base* b) {
	b->i++;
}

int main() {
	
	// pointer examples
	int x = 10;
	int* p = &x;		// you need & to get a pointer
	*p = 7;				// use * to assign to x through p
	int x2 = *p;		// read x through p
	int* p2 = &x2;		// get a pointer to another int
	p2 = p;				// p2 and p both point to x
	p = &x2;			// make p point to another object

	// reference examples
	int y = 10;
	int& r = y;			// r is of type reference to int
	r = 7;				// assign to y directly through r
	int y2 = r;			// read y directly through r
	int& r2 = y2;		// get a ref to another int
	r2 = r;				// the value of y is assigned to y2
	//r = &y2;			// error: you can't change the value of reference
						// (no assignment of an int* to an int&)

	/* 
		Pointers, references, and inheritance: we can express the idea
		of inheritance in terms of pointers or references: a pointer to the
		derived class can be implicitly converted into a pointer to the base
		class;
		*/

	void increment(Base * b);	// increment the sole member of the class

	Base* pb = new Derived;
	Derived d;

	increment(pb);
	increment(&d);
	increment(&d);

	std::cout << "Base pointer's member value: " << pb->i << std::endl;
	std::cout << "Derived object's member value: " << d.i << std::endl;

	std::cout << "Freeing the heap..." << std::endl;
	delete pb;
}