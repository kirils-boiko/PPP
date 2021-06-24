

/*
*	Header for the vector class;
	*/

#include <initializer_list>
#include <algorithm>
#include <iostream>
#include <memory>

struct out_of_range {	// class used to report range access errors
	/* ... */
};

template<typename T, typename A = std::allocator<T>>
class vector {		// read "for all types T> (just like in math)
	/*	invariant:
	*		if 0 <= n < sz, elem[n] is element n
	*		sz <= space;
	*		if sz < space there is space for (space - sz) double after elem[sz - 1];
	*/
protected: 
	A alloc;		// use allocate to handle memory for elements
	unsigned long sz;			// the size
	unsigned long space;		// total amount of space allocated (number of elements + number of free slots)
	T* elem;		// a pointer to the elements
public:

	using size_type = unsigned long;
	using value_type = T;
	using iterator = T*;
	using const_iterator = const T*;

	explicit vector();
	explicit vector(size_type s);							// constructor
	explicit vector(std::initializer_list<T> lst);	// initializer-list constructor

	vector(const vector&);							// copy constructor
	vector& operator=(const vector&);				// copy assignment
	vector(vector&& arg);							// move constructor
	vector& operator=(vector&&);					// move assignment

	~vector();										// destructor

	T& at(size_type n);									// checked access
	const T& at(size_type n) const;						// checked access for const vector
	T& operator[](size_type n);							// unchecked subscript operator
	T operator[](size_type n) const;						// unchecked const subscript operator

	iterator begin();
	const_iterator begin() const;
	iterator end();
	const_iterator end() const;

	iterator insert(iterator p, const T& val);
	iterator erase(iterator p);

	size_type size() const;							// returning the number of initialized elements
	void reserve(size_type);								// add space for new elements
	size_type capacity() const;							// return the amount of free space available
	void resize(size_type, T val = T());					// resize the vector
	void push_back(const T&);						// add an element to the end of the vector

	void print();

};


//-----------------------------------------------------------------------------------
// Constructors, assignments, and destructors

template<class T, class A> vector<T, A>::vector()		// default constructor
	:sz{ 0 }, elem{ nullptr }, space{ 0 } {}

template<class T, class A> vector<T, A>::vector(size_type s)	// constructor
	: sz{ s }, elem{ new T[s] }, space{ s }
{
	for (size_type i = 0; i < s; i++)
		elem[i] = 0;
}

template<class T, class A> vector<T, A>::vector(std::initializer_list<T> lst)		// initializer-list constructor
	:sz{ static_cast<int>(lst.size()) }, elem{ new T[sz] }, space{ static_cast<int>(lst.size()) }	// uninitializer mem for elems
{
	std::copy(lst.begin(), lst.end(), elem);				// initialize
}


template<typename T, typename A> vector<T, A>::vector(const vector<T, A>& arg)	// copy constructor
// allocate elements, then initialize them by copying
	:sz{ arg.sz }, elem{ new T[arg.sz] }, space{ arg.sz }
{
	std::copy(arg.elem, arg.elem + arg.sz, elem);
}

template<typename T, typename A> vector<T, A>& vector<T, A>::operator=(const vector<T, A>& arg)	// copy assignment
	// make this vector a copy of arg
	// operator= is regarded as a member function here, so it can directly
	//	refer to the members and use this pointer
{
	if (this == &arg) return *this;				// self-assignment, no work needed

	if (arg.sz <= space) {						// enough space, no need for new allocation
		for (size_type i = 0; i < arg.sz; ++i) elem[i] = arg.elem[i];	// copy elements
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

template<typename T, typename A> vector<T, A>::vector(vector<T, A>&& arg)
	:sz{ arg.sz }, elem{ arg.elem }, space{ arg.space }		// copy arg's elem pointer and size
{
	arg.sz = arg.space = 0;
	arg.elem = nullptr;
}

template<class T, class A> vector<T, A>& vector<T, A>::operator=(vector<T, A>&& arg)	// move arg to this vector
{
	delete[] elem;				// deallocate old space
	elem = arg.elem;
	sz = arg.sz;
	space = arg.space;
	arg.elem = nullptr;
	arg.sz = arg.space = 0;
	return *this;
}

template<class T, class A> vector<T, A>::~vector() { delete[] elem; }			// destructor


//-----------------------------------------------------------------------------------
// Access

template<class T, class A> T& vector<T, A>::at(size_type n) 
{
	if (n < 0 || n >= sz) throw out_of_range();
	return elem[n];
}

template<class T, class A> const T& vector<T, A>::at(size_type n) const
{
	if (n < 0 || n >= sz) throw out_of_range();
	return elem[n];
}

template<class T, class A> T& vector<T, A>::operator[](int n) { return elem[n]; }			// subscript operator

template<class T, class A> T vector<T, A>::operator[](int n) const { return elem[n]; }		// const subscript operator


//-----------------------------------------------------------------------------------
// Iterators

template<class T, class A> vector<T, A>::iterator vector<T, A>::begin()
{
	return &elem[0];
}

template<class T, class A> vector<T, A>::const_iterator vector<T, A>::begin() const
{
	return &elem[0];
}

template<class T, class A> vector<T, A>::iterator vector<T, A>::end()
{
	return &elem[sz];
}

template<class T, class A> vector<T, A>::const_iterator vector<T, A>::end() const
{
	return &elem[sz];
}


//-----------------------------------------------------------------------------------
// List-like operations

template<typename T, typename A>
vector<T,A>::iterator vector<T,A>::insert(iterator p, const T& val)
{
	int index = p - begin();						// remember an index, since memory addresses can be changed
	if (size() == capacity())
		reserve(size() == 0 ? 8 : 2 * size * ());	// make sure we have space

	// first copy last element into uninitialized space
	alloc.construct(elem + sz, *back());
	++sz;

	iterator pp = begin() + index;					// place to put val
	for (auto pos = end() - 1; pos != pp; --pos)
		*pos = *(pos - 1);							// copy element one position to the right
	*(begin() + index) = val;						// insert val
	return pp;
}

template<typename T, typename A>
vector<T, A>::iterator vector<T, A>::erase(iterator p)
{
	if (p == end())
		return p;
	for (auto pos = p + 1; pos != end(); ++pos)
		*(pos - 1) = *pos;							// copy element "one position to the left"
	alloc.destroy(&*(end() - 1));					// destroy surplus copy of last element
	--sz;
	return p;
}


//-----------------------------------------------------------------------------------
// Size, space, and memory member functions

template<class T, class A> vector<T, A>::size_type vector<T, A>::size() const { return sz; }

template<class T, class A> void vector<T, A>::reserve(size_type newalloc)
{
	if (newalloc <= space) return;					// never decrease allocation
	T* p = alloc.allocate(newalloc);				// allocate new space
	for (size_type i = 0; i < sz; ++i) alloc.construct(&p[i], elem[i]);	// copy old elements
	for (size_type i = 0; i < sz; ++i) alloc.destroy(&elem[i]);			// destroy old elements
	alloc.deallocate(elem, space);									// deallocate old space
	elem = p;
	space = newalloc;
}

template<class T, class A> int vector<T, A>::capacity() const { return space; }

template<class T, class A> void vector<T, A>::resize(size_type newsize, T val)
// make the vector have newsize elements
// initialize each new element with the default value of 0.0
// use T() as the default value unless the user says otherwise - to solve the problem
//	of lack of default values for some of the types used as template arguments;
{
	reserve(newsize);		// let reserve() do the hardwork with memory
	for (size_type i = sz; i < newsize; ++i) alloc.construct(&elem[i], val);		// initialize new elements
	for (size_type i = newsize; i < sz; ++i) alloc.destroy(&elem[i]);				// if resizing to smaller vector
	sz = newsize;
}

template<class T, class A> void vector<T, A>::push_back(const T& val)
// increase vector size by one; initialize the new element with d
{
	if (space == 0)
		reserve(8);						// start with space for 8 elements if vector is empty
	else if (sz == space)
		reserve(2 * space);				// get T the space if there is no spare space
	alloc.construct(&elem[sz], val);	// add val to the end
	++sz;								// increment the size by 1
}


//-----------------------------------------------------------------------------------
// Supporting functions

template<class T, class A> void vector<T, A>::print()
{
	std::cout << "{ ";
	for (size_type i = 0; i < sz; i++) std::cout << elem[i] << " ";
	std::cout << "}";
}
