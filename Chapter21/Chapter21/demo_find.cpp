
/*	Illustrating the definition and use of the simplest algorithm: find() 
*/

#include <vector>
#include <chrono>
#include <iostream>

template<typename In, typename T>
	// requires Input_Iterator<In>()
	//	&& Equality_comparable<Value_type><T>>()
In findx(In first, In last, const T& val)
// find the first element in [first, last) that equals val
// the iterator to one-beyond-the-last element is returned if not found
{
	while (first != last && *first != val)
		++first;
	return first;
}

void f(std::vector<int>& v, int x)
{
	auto p = findx(v.begin(), v.end(), x);
	if (p != v.end()) {
		// x is found
	}
	else {
		// x is not found
	}
	// ...
}

template<typename In, typename T>
// requires Input_Iterator<In>()
//	&& Equality_comparable<Value_type><T>>()
In findx_alt(In first, In last, const T& val)
// find the first element in [first, last) that equals val
// the iterator to one-beyond-the-last element is returned if not found
// less efficient representation of the loop - "the pedestrian way";
// somehow, this representation is actually faster than findx
{
	for (In p = first; p != last; ++p)
		if (*p == val)
			return p;
	return last;
}

long long avg(std::vector<int>& v)
	// calculate the average of elements in the vector
{
	long long sum = 0;
	for (int i = 0; i < v.size(); i++)
		sum += v[i];
	return sum / v.size();
}

constexpr int iterations = 1000000;
constexpr int simulations = 50;
constexpr int to_find = 999999;

int main()
{
	std::vector<int> v;
	for (int i = 0; i < iterations; i++)
		v.push_back(i);
	
	std::vector<int> times;
	std::vector<int> times01;

	for (int i = 0; i < simulations; i++) {
		auto start = std::chrono::high_resolution_clock::now();
		auto p = findx(v.begin(), v.end(), to_find);
		auto stop = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
		times.push_back(duration.count());
	}
	

	for (int i = 0; i < simulations; i++) {
		auto start = std::chrono::high_resolution_clock::now();
		auto p = findx_alt(v.begin(), v.end(), to_find);
		auto stop = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
		times01.push_back(duration.count());
	}

	std::cout << "Average time for findx (n = 1000000): " << avg(times) << " microseconds" << std::endl;
	std::cout << "Average time for findx_alt (n = 1000000): " << avg(times01) << " microseconds" << std::endl;
}