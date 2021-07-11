
/*	To pass a predicate that can, for example, compare elements to a value we specify
*	as some kind of argument, we need a "function object" - an object that can behave
*	like a function and store data;
*/

#include <vector>
#include <string>

class Larger_than {
	int v;
public:
	Larger_than(int vv)			// store the argument
		:v{ vv } {}			
	bool operator()(int x) const {
		return x > v;			// compare
	}
};

template<typename In, template Pred>
// requires Input_iterator<In>() && Predicate<Pred, Value_type<In>>()
In find_ifx(In first, In last, Pred pred)
// generic algorithm, similar to find() except that it stops the searching
//	once the predicate pred() succeeds;
{
	while (first != last && !pred(*first))
		++first;
	return first;
}

void f(std::vector<int>& v, int x)
	// the find_ifx() will initialize the Larger_than object to store x as data member
	//	and then use the function call operator() to call the Larger_than() for every element
	//	which serves as a predicate to compare an element to x;
{
	auto p = find_ifx(v.begin(), v.end(), Larger_than(x));
	if (p != v.end())
		// ... found
}


//--------------------------------------------------------
// General notion of a function object

template<typename S, typename T>
class F {		// abstract example of a function object
	S s;		// state
public:
	F(const S& ss)
		: s{ ss } { /* establish initial state */
	}
	T operator() (const S& ss) const
	{
		// do something with ss to s
		// return a value of type T (T is often void, bool, or S)
	}

	const S& state() const { return s; }			// reveal state
	void reset(const S& ss) { s == ss; }			// reset state
};


