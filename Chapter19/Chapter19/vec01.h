
/*	When compared to v00.h, this version uses the vector_base struct as the 
*	private base for the vector class that manages the memory for a vector;
*	Does not compile;
*	The new implementation of reserve is suspicious;
*/

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

template<typename T, typename A>
struct vector_base {
	A alloc;
	T* elem;		// start of allocation
	int sz;			// number of elements
	int space;		// amount of allocated space

	vector_base(const A& a, int n)
		:alloc{ a }, elem{ alloc.allocate(n) }, sz{ n }, space{ n } {}
	~vector_base() { alloc.deallocate(elem, space); }
};

template<typename T, typename A = std::allocator<T>>
class vector : private vector_base<T,A> {		// read "for all types T> (just like in math)
	// a convenient interface to vector_base
public:

	using vector_base<T, A>::vector_base;

	explicit vector();

	explicit vector(int s);									// constructor

	explicit vector(std::initializer_list<T> lst);		// initializer-list constructor

	vector(const vector&);							// copy constructor

	vector& operator=(const vector&);				// copy assignment

	vector(vector&& arg);							// move constructor

	vector& operator=(vector&&);					// move assignment

	T& at(int n);									// checked access

	const T& at(int n) const;						// checked access for const vector

	T& operator[](int n);							// unchecked subscript operator

	T operator[](int n) const;						// unchecked const subscript operator

	~vector();										// destructor

	int size() const;								// returning the number of initialized elements

	void reserve(int);								// add space for new elements

	int capacity() const;							// return the amount of free space available

	void resize(int, T val = T());							// resize the vector

	void push_back(const T&);						// add an element to the end of the vector

	void print();

};


template<class T, class A> vector<T, A>::vector()		// default constructor
	:sz{ 0 }, elem{ nullptr }, space{ 0 } {}

template<class T, class A> vector<T, A>::vector(int s)	// constructor
	: sz{ s }, elem{ new T[s] }, space{ s }
{
	for (int i = 0; i < s; i++)
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

template<class T, class A> T& vector<T, A>::at(int n)
{
	if (n < 0 || n >= sz) throw out_of_range();
	return elem[n];
}

template<class T, class A> const T& vector<T, A>::at(int n) const
{
	if (n < 0 || n >= sz) throw out_of_range();
	return elem[n];
}

template<class T, class A> T& vector<T, A>::operator[](int n) { return elem[n]; }			// subscript operator

template<class T, class A> T vector<T, A>::operator[](int n) const { return elem[n]; }		// const subscript operator

template<class T, class A> vector<T, A>::~vector() { delete[] elem; }			// destructor

template<class T, class A> int vector<T, A>::size() const { return sz; }

template<class T, class A> void vector<T, A>::reserve(int newalloc)
{
	// uninitialized_copy is used to construct copies of elements from b because
	//	it correctly handles throws;
	// when we exit reserve(), the old allocation is automatically freed by the
	//	vector_base's destructor;
	// if instead, the exception from copying is thrown, the new allocation is freed;
	// since *this and b are of different types (vector and vector_base) we use swap
	//	with template arguments to swap the objects;
	if (newalloc <= space) return;					// never decrease allocation
	vector_base<T, A> b(this->alloc, newalloc);		// allocate new space
	std::uninitialized_copy(this->elem, &this->elem[this->sz], b.elem);		// copy
	for (int i = 0; i < sz; ++i)
		this->alloc.destroy(&this->elem[i]);		// destroy old elements
	std::swap<vector_base<T, A>>(*this, b);			// swap representations
}

template<class T, class A> int vector<T, A>::capacity() const { return space; }

template<class T, class A> void vector<T, A>::resize(int newsize, T val)
// make the vector have newsize elements
// initialize each new element with the default value of 0.0
// use T() as the default value unless the user says otherwise - to solve the problem
//	of lack of default values for some of the types used as template arguments;
{
	reserve(newsize);		// let reserve() do the hardwork with memory
	for (int i = sz; i < newsize; ++i) alloc.construct(&elem[i], val);		// initialize new elements
	for (int i = newsize; i < sz; ++i) alloc.destroy(&elem[i]);				// if resizing to smaller vector
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

template<class T, class A> void vector<T, A>::print()
{
	std::cout << "{ ";
	for (int i = 0; i < sz; i++) std::cout << elem[i] << " ";
	std::cout << "}";
}


//-----------------------------------------------------------
//	Supporting functions

template<class T, class A> vector<T, A> fill(std::istream& is)
{
	vector<T, A> res;
	for (T x; is >> x; ) res.push_back(x);
	return res;
}



//-----------------------------------------------------------
//	Previous versions of member functions (just FYI)

//template<class T, class A> void vector<T, A>::reserve(int newalloc)
//{
//	if (newalloc <= space) return;					// never decrease allocation
//	T* p = new T[newalloc];							// allocate new space, previously done using new T[new
//	for (int i = 0; i < sz; ++i) p[i] = elem[i];	// copy old elements
//	delete[] elem;									// deallocate old space
//	elem = p;
//	space = newalloc;
//}


//template<class T, class A> void vector<T, A>::push_back(T d)
//// increase vector size by one; initialize the new element with d
//{
//	if (space == 0)
//		reserve(8);				// start with space for 8 elements if vector is empty
//	else if (sz == space)
//		reserve(2 * space);		// get T the space if there is no spare space
//	elem[sz] = d;				// add d at end
//	++sz;						// increment the size by 1
//}