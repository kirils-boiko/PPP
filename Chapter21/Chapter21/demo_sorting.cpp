
/*	Ordering the data can be achieved either by using a data structure that maintains order such as
*	map and set, or by sorting (e.g., using the STL sort() algorithm);
*	By default, the STL sort() uses < as sorting criterion;
*	To illustrate the sorting based on a user-specified criterion, example of string sorting
*	without taking case into account is presented;
*/

/*
template<typename Ran>
	// requires Random_access_iterator<Ran>()
void sort(Ran first, Ran last);

template<typename Ran, typename Cmp>
	// requires Random_access_iterator<Ran>()
	// && Less_than_comparable<Cmp, Value_type<Ran>>()
void sort(Ran first, Ran last, Cmp cmp);
*/

#include <string>
#include <cctype>
#include <algorithm>
#include <vector>
#include <iostream>

struct No_case {		// is lowercase(x) < lowercase(y)?
	bool operator()(const std::string& x, const std::string& y) const
	{
		for (int i = 0; i < x.length(); ++i) {
			if (i == y.length())
				return false;			// y < x
			char xx = std::tolower(x[i]);
			char yy = std::tolower(y[i]);
			if (xx < yy) return true;	// x < y
			if (yy < xx) return false;	// y < x
		}
		if (x.length() == y.length()) return false;		// x == y
		return true;					// x < y (fewer characters in x)
	}
};

void sort_and_print(std::vector<std::string>& vc)
{
	std::sort(vc.begin(), vc.end(), No_case());
	
	for (const auto& s : vc)
		std::cout << s << std::endl;
}