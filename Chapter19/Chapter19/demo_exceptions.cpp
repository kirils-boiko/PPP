
/*	A common resource management problem of memory leaks is solved by 
	using the RAII principle;
	However, if the object created using RAII cannot be kept within a single scope
	and its sub-scopes (it is common to call a function to construct a complicated data
	structure and return that data structure as the result), memory leaks are still possible;
	Thus, you can use try-catch blocks to guarantee that the resource is managed and
	released well;

	However, that try-catch code is still ugly so the solution would to somehow
	use RAII by providing an object to hold that vector<int> so that it can delete the
	vector if an exception occurs;
	The STL unique_ptr offers this functionality;

	What's more, someone might forget to destroy the released unique ptr so to avoid
	that you can also return the unique_ptr!

	There's one more catch: returning by moving;
	If you create a vector on stack and then use a move constructor to get the ownership
	of elements out of the function, it's gonna be the simplest solution
	*/

#include "vec00.h"
#include <memory>

vector<int>* unsafe_make()				// make a filled vector
{
	vector<int>* p = new vector<int>;	// allocate on free store
	// ... fill the vector with data; this may throw an exception ...
	return p;
}

vector<int>* safe_make()				// make a filled vector
{
	vector<int>* p = new vector<int>;	// allocate on free store
	try {
		// fill the vector with data; this may throw an exception
		return p;
	}
	catch (...) {
		delete p;						// do the local cleanup
		throw;							// re-throw to allow our caller to deal with the fact that safe_make() couldn't do what was required of it;
	}
}

vector<int>* safer_make()					// make a filled vectorr
{
	std::unique_ptr<vector<int>> p{ new vector<int> };	// allocate on the free store
	// ... fill the vector with data; this may throw an exception
	return p.release();					// return the pointer held by p
}

std::unique_ptr<vector<int>> safest_make()
{
	std::unique_ptr<vector<int>> p{ new vector<int> };	// allocate on the free store
	// ... fill the vector with data; this may throw an exception
	return p;					// return the unique ptr
}

vector<int> simplest_make()
{
	vector<int> res;
	// ... fill the vector with data; this may throw an exception but you have proper destructors invoked
	return res;			// the move constructor efficiently transfers ownership;
}