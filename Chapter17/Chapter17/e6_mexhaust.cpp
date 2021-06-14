
/* 
	Running out of memory using the new operator by the use of infinite loop
	that allocates but never deallocates
	*/

#include <iostream>

constexpr int N_ELEMENTS = 1000000;

int main()
{
	unsigned long long malloc = 0;
	while (true) {
		int* p = new int[N_ELEMENTS];
		malloc += N_ELEMENTS * sizeof(int);
		std::cout << "Memory allocated:\t" << malloc/1000000 << " MB" << std::endl;
	}
}