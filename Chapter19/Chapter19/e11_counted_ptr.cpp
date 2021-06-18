
/*	Simple implementation of Counted_ptr<T> that is a type that holds a pointer to an
*	object of type T and an int pointer to a "use count" shared by all counted pointers to
*	the same ofbject of type T;
*	The use count holds the number of Counted_ptr to a given T;
*	Counted_ptr's constructor allocates a T object and a use count on the free store, and takes
*	in initial value of the T elements as the argument;
*	When the last Counted_ptr is destroyed, Counted_ptr's destructor should delete the T;
*	Also, operations for using it as a pointer are provided;
*/

#include <memory>
#include <iostream>
#include <vector>

template<typename T>
class Counted_ptr {
	T* m_ptr = nullptr;
	int* m_count = nullptr;	// pointer to the use count

public:
	explicit Counted_ptr(T obj = T{}) {				// constructor
		m_ptr = (T*)(std::malloc(sizeof(T)));
		new ((void*)m_ptr) T{ obj };
		m_count = (int*)(std::malloc(sizeof(int)));
		new ((void*)m_count) int{ 1 };
		std::cerr << this << ": Counted_ptr's constructor called; heap memory allocated at:" << std::endl
			<< m_ptr << ": T object;" << std::endl
			<< m_count << ": use count;" << std::endl;
	}

	Counted_ptr(Counted_ptr<T>& arg) {			// Copy constructor
		m_ptr = arg.m_ptr;
		m_count = arg.m_count;
		(*m_count)++;
		std::cerr << this << ": Counted_ptr object allocated on stack, initialized with Counted_ptr's copy constructor; no heap memory allocation;" << std::endl;
	}

	Counted_ptr& operator=(const Counted_ptr<T>& arg) {		// copy assignment
		
		// manage the old memory and use count
		this->~Counted_ptr();

		m_ptr = arg.m_ptr;
		m_count = arg.m_count;
		(*m_count)++;
		std::cerr << this << ": Copy assignment called; no heap memory allocation; assigned from " << &arg << std::endl;

		return *this;
	}

	~Counted_ptr() {							// Destructor
		if ((--(*m_count)) == 0) {
			std::cerr << this << ": Counted_ptr's destructor called; heap memory deallocated at:" << std::endl
				<< m_ptr << ": T object;" << std::endl
				<< m_count << ": use count;" << std::endl;
			std::free(m_ptr);
			std::free(m_count);
		}
		else
			std::cerr << this << ": Counter_ptr's destructor called; no heap memory deallocation;" << std::endl;
	}

	T& operator*() { return *m_ptr; }
	T* operator->() const { return m_ptr; }

	int count() const { return *m_count; }
	T* get() const { return m_ptr; }
};


int main()
{
	Counted_ptr<int> cp_i00{ 10 };
	Counted_ptr<int> cp_i01{ cp_i00 };
	Counted_ptr<int> cp_i02;
	cp_i02 = cp_i01;

	std::cerr << "----------------------------------" << std::endl;

	Counted_ptr<std::vector<int>> cp_vi00{ std::vector<int>(10) };
	Counted_ptr<std::vector<int>> cp_vi01{ {1, 2, 3, 4, 5} };
	Counted_ptr<std::vector<int>> cp_vi02;
	cp_vi02 = cp_vi01;

	std::cerr << "----------------------------------" << std::endl;
}