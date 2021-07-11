
/*	Drill Part 3: More Vector Use 
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <string>
#include <numeric>
#include <functional>

template<typename T>
void print_vector(std::vector<T>& v)
{
	std::cout << "{ ";
	for (int i = 0; i < v.size() - 1; i++)
		std::cout << v[i] << ", ";
	std::cout << v[v.size() - 1] << " }" << std::endl;
}

int main()
{
	std::string from;

	std::cout << "Enter the input file name:" << std::endl;
	std::cin >> from;
	std::ifstream is{ from };

	std::vector<double> vd;
	if (is.is_open()) {
		std::istream_iterator<double> ii{ is };
		std::istream_iterator<double> eos{};
		std::ostream_iterator<double> oi{ std::cout, ", " };
		vd = std::vector<double>{ ii, eos };
	}
	
	print_vector(vd);

	std::vector<int> vi(vd.size());
	std::copy(vd.begin(), vd.end(), vi.begin());

	for (int i = 0; i < vd.size(); i++)
		std::cout << '(' << vd[i] << ',' << vi[i] << ')' << std::endl;

	std::cout << "Sum of the elements of vector of doubles, vd: " <<
		std::accumulate(vd.begin(), vd.end(), 0.0) << std::endl;

	std::cout << "Sum of the differences between elements of vd and elements of vi: " <<
		std::inner_product(vd.begin(), vd.end(), vi.begin(), 0.0, std::plus<double>(), std::minus<double>()) << std::endl;

	std::reverse(vd.begin(), vd.end());
	std::cout << "Reversed vector of doubles: ";
	print_vector(vd);

	int size = vd.size();
	std::cout << "Mean value of the elements in vd: " << std::accumulate(vd.begin(),
		vd.end(), 0.0, [size](double init, double elem) { return init + elem / size; })
		<< std::endl;

	double vd_mean = std::accumulate(vd.begin(),
		vd.end(), 0.0, [size](double init, double elem) { return init + elem / size; });

	std::vector<double> vd2(vd.size());
	auto it = std::copy_if(vd.begin(), vd.end(), vd2.begin(), [vd_mean](double elem) {
		return elem < vd_mean; });
	vd2.resize(std::distance(vd2.begin(), it));		// shrink vector to new size

	std::sort(vd2.begin(), vd2.end());
	std::sort(vd.begin(), vd.end());

	std::cout << "vd: ";
	print_vector(vd);

	std::cout << "vd2: ";
	print_vector(vd2);
}
