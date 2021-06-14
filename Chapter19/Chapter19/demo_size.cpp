
/*	This source file's sole purpose is to provide notes;
*	The actual implementation is done in myVector.cpp and myVector.h
*/

/*	Changing the size of a vector starts from the most fundamental operation: reserve()
*	It is used add (reserve) space for new elements;
*	Note that the elements of the reserved space are not initialized by reserve - it's done by
*	push_back() and resize();
	*/

/*	resize() member operation handles the following cases:
*	- new size is larger than the old allocation
*	- new size if larger than the old size, but smaller than or equal to the old allocation
*	- the new size is equal to the old size
*	- the new size is smaller than the old size;
	*/

/*	push_back() method is rather straightforward once the reserve() is implemented;
	*/

/*	The vector's copy assignment does copy the elements but does not copy the spare space;
*	The implementation is rather simple:
*	- allocate memory for a copy;
*	- copy the elements;
*	- delete the old allocation
*	- set the sz, elem, and space to new values;
*	A more efficient eway of copying elements is to copy those into already available space
*	in the target vector;
	*/