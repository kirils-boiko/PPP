
/*
*	Member function and supporting function definitions for vector class
*	declared in myVector.h
*/

#include "myVector.h"

template<class T> vector<T>::vector()		// default constructor
	:sz{ 0 }, elem{ nullptr }, space{ 0 } {}

template<class T> vector<T>::vector(int s)	// constructor
	: sz{ s }, elem{ new T[s] }, space{ s }
{
	for (int i = 0; i < s; i++)
		elem[i] = 0;
}

template<class T> vector<T>::vector(std::initializer_list<T> lst)		// initializer-list constructor
	:sz{ static_cast<int>(lst.size()) }, elem{ new T[sz] }, space{ static_cast<int>(lst.size()) }	// uninitializer mem for elems
{
	std::copy(lst.begin(), lst.end(), elem);				// initialize
}


template<typename T> vector<T>::vector(const vector<T>& arg)	// copy constructor
// allocate elements, then initialize them by copying
	:sz{ arg.sz }, elem{ new T[arg.sz] }, space{ arg.sz }
{
	std::copy(arg.elem, arg.elem + arg.sz, elem);
}

template<typename T> vector<T>& vector<T>::operator=(const vector<T>& arg)	// copy assignment
	// make this vector a copy of arg
	// operator= is regarded as a member function here, so it can directly
	//	refer to the members and use this pointer
{
	if (this == &arg) return *this;				// self-assignment, no work needed

	if (arg.sz <= space) {						// enough space, no need for new allocation
		for (int i = 0; i < arg.sz; ++i) elem[i] = arg.elem[i];	// copy elements
		sz = arg.sz;
		return *this;
	}

	T* p = new T[arg.sz];				// allocate new space
	std::copy(arg.elem, arg.elem + arg.sz, p);	// copy elements
	delete[] elem;								// deallocate old space
	space = sz = arg.sz;						// set the new size and space
	elem = p;									// reset to the newly allocated elements
	return *this;								// return a self reference
}

template<typename T> vector<T>::vector(vector<T>&& arg)
	:sz{ arg.sz }, elem{ arg.elem }, space{ arg.space }		// copy arg's elem pointer and size
{
	arg.sz = arg.space = 0;
	arg.elem = nullptr;
}

template<class T> vector<T>& vector<T>::operator=(vector<T>&& arg)	// move arg to this vector
{
	delete[] elem;				// deallocate old space
	elem = arg.elem;
	sz = arg.sz;
	space = arg.space;
	arg.elem = nullptr;
	arg.sz = arg.space = 0;
	return *this;
}

template<class T> T& vector<T>::operator[](int n) { return elem[n]; }			// subscript operator

template<class T> T vector<T>::operator[](int n) const { return elem[n]; }		// const subscript operator

template<class T> vector<T>::~vector() { delete[] elem; }			// destructor

template<class T> int vector<T>::size() const { return sz; }

template<class T> void vector<T>::reserve(int newalloc)
{
	if (newalloc <= space) return;					// never decrease allocation
	T* p = new T[newalloc];				// allocate new space
	for (int i = 0; i < sz; ++i) p[i] = elem[i];	// copy old elements
	delete[] elem;									// deallocate old space
	elem = p;
	space = newalloc;
}

template<class T> int vector<T>::capacity() const { return space;  }

template<class T> void vector<T>::resize(int newsize)
	// make the vector have newsize elements
	// initialize each new element with the default value of 0.0
{
	reserve(newsize);		// let reserve() do the hardwork with memory
	for (int i = sz; i < newsize; ++i) elem[i] = 0;		// initialize new elements
	sz = newsize;
}

template<class T> void vector<T>::push_back(T d)
// increase vector size by one; initialize the new element with d
{
	if (space == 0)
		reserve(8);				// start with space for 8 elements if vector is empty
	else if (sz == space)		
		reserve(2 * space);		// get T the space if there is no spare space
	elem[sz] = d;				// add d at end
	++sz;						// increment the size by 1
}

template<class T> void vector<T>::print()
{
	std::cout << "{ ";
	for (int i = 0; i < sz; i++) std::cout << elem[i] << " ";
	std::cout << "}";
}


//-----------------------------------------------------------
//	Supporting functions

template<class T> vector<T> fill(std::istream& is)
{
	vector<T> res;
	for (T x; is >> x; ) res.push_back(x);
	return res;
}


