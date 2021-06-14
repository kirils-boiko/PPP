
/* 
	Illustrating the use of void*;
	Since the compiler doesn't know what a void* points to,
	we must explicitly cast the ptr into required type;
	*/

void f(void* pv) {
	void* pv2 = pv;			// copying is OK
	double* pd = pv;		// error: cannot convert void* to double*
	*pv = 7;				// error: cannot dereference a void*
	pv[2] = 9;				// error: cannot subscript a void*

	int* pi = static_cast<int*>(pv);	// OK: explicit conversion
}

/* Examples of reinterpret_cast and const_cast: */

// Telling the compiler that a part of memory starting with
//	location 0xFF is to be considered a Register;
Register* in = reinterpret_cast<Register*>(0xff);

void f(const Buffer* p) {
	Buffer* b = const_cast<Buffer*>(p);		// pointer b is not const anymore
}