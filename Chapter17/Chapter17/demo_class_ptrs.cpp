
/* 
	Since the notion of pointers is general, you can point
	to just about anything that can be placed in memory;
	*/

#include <vector>

std::vector<int>* f(int s) {
	std::vector<int>* p = new std::vector<int>(s);		// allocate a vector on free store
	// fill *p
	return p;
}

void ff() {
	std::vector<int>* q = f(4);
	// use *q
	delete q;		// free vector on free store
}