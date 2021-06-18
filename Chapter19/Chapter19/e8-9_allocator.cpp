
/*	Implementing a simple allocator using the basic allocation functions malloc() and free();
	Getting the vector from 19.4 to work for a few simple test cases;
	Parts of the solution are adapted from the work of Nicolai M. Josuttis 1999 in
	The C++ Standard Library - A Tutorial and Reference
	http://www.josuttis.com/libbook/memory/myalloc.hpp.html;
	Parts of the solution are also adapted from: 
	https://en.cppreference.com/w/cpp/named_req/Allocator
*/

#include <iostream>
#include <stdexcept>
#include <limits>
#include <memory>
#include <algorithm>
#include <initializer_list>

constexpr int maxsz = 9;

template<typename T>
class Allocator;

struct out_of_range {	// class used to report range access errors
	/* ... */
};

template<typename T, typename A = Allocator<T>>
class vector {		// read "for all types T> (just like in math)
	/*	invariant:
	*		if 0 <= n < sz, elem[n] is element n
	*		sz <= space;
	*		if sz < space there is space for (space - sz) double after elem[sz - 1];
	*/
protected:
	A alloc;		// use allocate to handle memory for elements
	int sz;			// the size
	int space;		// total amount of space allocated (number of elements + number of free slots)
	T* elem;		// a pointer to the elements
public:

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

	T* p = alloc.allocate(arg.sz);				// allocate new space
	std::copy(arg.elem, arg.elem + arg.sz, p);	// copy elements

	alloc.deallocate(elem, space);				// deallocate old space
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
	alloc.deallocate(elem, space);				// deallocate old space
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
	if (newalloc <= space) return;					// never decrease allocation
	T* p = alloc.allocate(newalloc);				// allocate new space
	for (int i = 0; i < sz; ++i) alloc.construct(&p[i], elem[i]);	// copy old elements
	for (int i = 0; i < sz; ++i) alloc.destroy(&elem[i]);			// destroy old elements
	alloc.deallocate(elem, space);									// deallocate old space
	elem = p;
	space = newalloc;
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



//-------------------------------------------------
// Simple allocator

template<typename T> class Allocator {
public:
	// type definitions
	typedef T				value_type;
	typedef T*				pointer;
	typedef const T*		const_pointer;
	typedef T&				reference;
	typedef const T&		const_reference;
	typedef std::size_t		size_type;

public:
	pointer allocate(size_type n)
		// allocate uninitialized memory for n objects of type T
	{
		if (n > std::numeric_limits<size_type>::max() / sizeof(T))
			throw std::bad_array_new_length();

		pointer ret = (pointer)(std::malloc(n * sizeof(T)));
		if (ret == nullptr)
			throw std::bad_alloc();

		std::cerr << "allocate " << n << " element(s)"
			<< " of size " << sizeof(T) << std::endl;
		std::cerr << "allocated at: " << (void*)ret << std::endl;
		return ret;
	}
	
	void deallocate(pointer p, size_type n)
		// deallocate memory for n objects of type T starting from p
	{
		std::cerr << "deallocate " << n << " element(s)"
			<< " of size " << sizeof(T)
			<< " at: " << (void*)p << std::endl;
		std::free((void*)p);
	}

	void construct(pointer p, const_reference v)
		// initialize element of allocated storage p with value v
	{
		new((void*)p)T{ v };
	}
	
	void destroy(pointer p)
		// destroy element of initialized storage using its destructor
	{
		p->~T();
	}
};


int main()
try {
	vector<int, Allocator<int>> v00;
	for (int i = 0; i < maxsz; i++) 
		v00.push_back(i);
	std::cout << "{ ";
	for (int i = 0; i < v00.size(); i++)
		std::cout << v00[i] << ' ';
	std::cout << '}' << std::endl;;

	vector<double> v01;
	for (int i = 0; i < maxsz*2; i++)
		v01.push_back(i);
	std::cout << "{ ";
	for (int i = 0; i < v01.size(); i++)
		std::cout << v01[i] << ' ';
	std::cout << '}' << std::endl;

	vector<double> v02;
	for (int i = 0; i < maxsz - 1; i++)
		v02.push_back(i*i);
	v02 = v01;
	std::cout << "{ ";
	for (int i = 0; i < v02.size(); i++)
		std::cout << v02[i] << ' ';
	std::cout << '}' << std::endl;



}
catch (std::bad_array_new_length) {
	std::cerr << "error: total size of the new array exceeds implementation-defined max value" << std::endl;
}
catch (std::bad_alloc) {
	std::cerr << "malloc: allocation failure" << std::endl;
}
catch (std::exception& e) {
	std::cerr << "error: " << e.what() << std::endl;
}










////-------------------------------------------------
//// Vector class from end of Section 19.4
//
//struct Range_error : std::out_of_range {	// enhanced vector range error reporting
//	std::size_t index;
//	Range_error(std::size_t i)
//		: std::out_of_range{ "Range error" }, index(i) {}
//};
//
//template<typename T, typename A = Allocator<T>> class Vector : public std::vector<T, A> {
//public:
//	using size_type = typename std::vector<T, A>::size_type;
//	using std::vector<T, A>::vector;			// use vector<T>'s constructors
//
//	T& operator[](size_type i)				// rather than return at(i);
//	{
//		if (i < 0 || i >= this->size())
//			throw Range_error{ i };
//		return std::vector<T, A>::operator[](i);
//	}
//
//	const T& operator[](size_type i) const
//	{
//		if (i < 0 || i >= this->size())
//			throw Range_error{ i };
//		return std::vector<T, A>::operator[](i);
//	}
//};
//
