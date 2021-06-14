
#include <iostream>

/*	Illustrating the use of arrays
	*/

const int max = 100;
int gai[max];			// global array of max number of ints

//void f(int n)
//{
//	char lac[20];		// local array
//	int lai[60];
//	//double lad[n];		// error: array size is not constant
//
//	lac[-2] = 'b';		// no error, but is disastrous: array does not range check
//}

int main()
{
	double ad[10];
	double* p = &ad[5];		// pointer to array element
	p += 2;					// move p 2 elements to the right
	p -= 5;					// move p 5 elements to the left

	char ach[100];
	ach[0] = 'A';
	std::cout << sizeof(ach) << std::endl;		// printing the size of ach
	char* pch = ach;								// ch become a pointer to the first element
	std::cout << *pch << std::endl;
	
	char ac[] = "Bjorn";	// array of 6 characters due to the null terminating character; C-style string

	char chars[] = { 'a', 'b', 'c' };	// no terminating null character
	int ai[] = { 1, 2, 3, 4, 5, 6, 7 };	// just an array of ints initialized to the list of ints;


}


/*	Note: the name of an array refers to all the elements of the array;
*	However, the name of an array turns into a pointer when assigned to a pointer;
	*/

int strlen(const char *p)	// similar to the standard library strlen()
{
	int count = 0;
	while (*p) { ++count; ++p; }
	return count;
}

int strlen(const char a[])	// an array name is converted to a pointer, so passed by reference not by value
{
	int count = 0;
	while (a[count]) { ++count; }
	return count;
}

int Cstrlen(const char* p)	// strlen for C-style string, strlen() doesn't count the terminating 0
{
	int count = 0;
	while (p[count]) ++count;
	return count;
}
