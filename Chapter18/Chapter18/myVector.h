

/*
*	Header for the vector class;
	*/

#include <initializer_list>
#include <algorithm>
#include <iostream>

template<typename T>
class vector {		// read "for all types T> (just like in math)
	/*	invariant:
	*		if 0 <= n < sz, elem[n] is element n
	*		sz <= space;
	*		if sz < space there is space for (space - sz) double after elem[sz - 1];
	*/
protected:
	int sz;			// the size
	int space;		// total amount of space allocated (number of elements + number of free slots)
	T* elem;	// a pointer to the elements
public:

	explicit vector();

	explicit vector(int s);									// constructor

	explicit vector(std::initializer_list<T> lst);		// initializer-list constructor

	vector(const vector&);							// copy constructor

	vector& operator=(const vector&);				// copy assignment

	vector(vector&& arg);							// move constructor

	vector& operator=(vector&&);					// move assignment

	T& operator[](int n);						// subscript operator

	T operator[](int n) const;					// const subscript operator

	~vector();										// destructor

	int size() const;								// returning the number of initialized elements

	void reserve(int);								// add space for new elements

	int capacity() const;							// return the amount of free space available

	void resize(int);								// resize the vector

	void push_back(T d);						// add an element to the end of the vector

	void print();

};

