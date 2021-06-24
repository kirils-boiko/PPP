 
/*	A function that copies the elements of an array of ints into another without
*	using the subcription operators;
*/

void copy(int* f1, int* e1, int* f2)
	// copy the elements of an array defined by [f1:e1) into f2
{
	while (f1 != e1) {
		*f2 = *f1;
		f1++;
		f2++;
	}
}
