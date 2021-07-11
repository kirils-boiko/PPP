
/*	One of the most simplest and efficient STL algorithms is copying algorithm;
	The STL provides three versions of copy: copy(), unique_copy(), copy_if()
*/

#include <vector>
#include <iostream>
#include <list>
#include <stdexcept>

// The basic copy algorithm
template<typename In, typename Out>
	// requires Input_operator<In>() && Output_iterator<Out>()
Out copyx(In first, In last, Out res)
{
	while (first != last) {
		*res = *first;		// copy element
		++first;
		++res;
	}
	return res;
}

void f(std::vector<double>& vd, std::list<int>& li)
	// copy the elements of a list of ints into a vector of doubles
{
	if (vd.size() < li.size())
		throw std::out_of_range("target container too small");
	copyx(li.begin(), li.end(), vd.begin());
	//...
}

int main()
try {
	std::vector<double> vd(5, 0);
	std::list<int> li{ 10, 20, 30, 40 };

	f(vd, li);

	for (auto& x : vd)
		std::cout << x << ' ';
	std::cout << std::endl;
}
catch (std::out_of_range& e) {
	std::cerr << "Range error: " << e.what() << std::endl;
}