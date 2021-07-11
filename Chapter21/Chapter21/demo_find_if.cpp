
/*	Illustrating the definition and use of the standard algorithm that searches based
*	on a user-supplied criterion, find_if(); 
*/

#include <vector>
#include <list>

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

bool odd(int x)
	// predicate checking whether an int is odd or not
{
	return x % 2;
}

bool larger_than_42(double x)
{
	return x > 42;
}

double v_val;			// the value to which larger_than_v() compares its argument
bool larger_than_v(double x)
	// more general-use predicate using an implicit argument v_val
{
	return x > v_val;
}

void f(std::vector<int>& v)
{
	auto p = find_ifx(v.begin(), v.end(), odd);
	if (p != v.end()) {
		// odd number is found
	}
	//...
}

void g(std::vector<double>& v)
{
	auto p = find_ifx(v.begin(), v.end(), larger_than_42);
	if (p != v.end()) {
		// value larger than 42 is found;
	}
	//...
}

void h(std::list<double>& l, int x)
{
	v_val = x;
	auto p = find_ifx(l.begin(), l.end(), larger_than_v);
	if (p != l.end())
	{
		// value larger than x is found
	}
	// ...
}