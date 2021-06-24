/*	Adapting built-in arrays to the STL: building an array container that provides
*	the benefits of arrays (i.e. modelling physical memory almost perfectly) without
*	the weaknesses such as lack of copy assignment operator, lack of size operation, etc;
*/

template <typename T, int N>
struct array {
	using value_type = T;
	using iterator = T*;
	using const_iterator = const T*;
	using size_type = unsigned int;		// the type of a subscript

	T elems[N];
	// no explicit construct/copy/destroy needed;

	iterator begin() { return elemns; }
	const_iterator begin() const { return elems; }
	iterator end() { return elems + N; }
	const_iterator end() const { return elems + N; }

	size_type size() const { return N; }

	T& operator[](int n) { return elems[n]; }
	const T& operator[](int n) const { return elems[n]; }

	const T& at(int n) const;				// range-checked access
	T& at(int n);							// range-checked access

	T* data() { return elems; }
	const T* data() const { return elems; }

};