
/* Drill Part 2: STL map
*/

#include <algorithm>
#include <map>
#include <string>
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <fstream>
#include <utility>
#include <numeric>

template<typename X, typename Y>
std::istream& read_pairs(std::istream& is, std::map<X, Y>& mp)
{
	while (is.good()) {
		char ch;
		is >> ch;
		if (is.eof())
			break;
		if (ch != '(')
			throw std::ios_base::failure("format error");

		X x;
		is >> x;
		is >> ch;
		if (ch != ',')
			throw std::ios_base::failure("format error");

		Y y;
		is >> y;
		is >> ch;
		if (ch != ')')
			throw std::ios_base::failure("format error");

		mp[x] = y;
	}
	return is;

}

template<typename X, typename Y>
struct Accum_second {			// BinOp for accumulating the .second of two maps 
	Y operator()(Y accum, const std::pair<X, Y>& pr)
	{
		return accum + pr.second;
	}
};

int main()
try {
	std::map<std::string, int> msi;
	msi["Bazemore"] = 26;
	msi["Bell"] = 7;
	msi["Curry"] = 30;
	msi["Green"] = 23;
	msi["Lee"] = 1;
	msi["Looney"] = 5;
	msi["Mannion"] = 2;
	msi["Mulder"] = 15;
	msi["Ouber Jr."] = 12;
	msi["Paschall"] = 7;

	std::cout << "Golden State Warriors Roster (name, number): " << std::endl;
	for (const auto& x : msi)
		std::cout << std::setw(10) << x.first << ": " << x.second << std::endl;

	msi.erase(msi.begin(), msi.end());

	std::ifstream file{ "d_map.txt" };

	read_pairs(file, msi);

	std::cout << std::endl << "Cleveland Cavaliers Roster (name, number): " << std::endl;
	for (const auto& x : msi)
		std::cout << std::setw(12) << x.first << ": " << x.second << std::endl;

	std::cout << "Sum of Roster numbers: " << std::accumulate(msi.begin(), msi.end(), 0, Accum_second<std::string, int>()) << std::endl;
	
	std::cout << std::endl << "=================================" << std::endl;
	std::cout << std::endl << "Cleveland Cavaliers Roster (number, name): " << std::endl;
	std::map<int, std::string> mis;
	for (const auto& x : msi)
		mis[x.second] = x.first;

	for (const auto& x : mis)
		std::cout << std::setw(3) << x.first << ": " << x.second << std::endl;

}
catch (std::ios_base::failure& f) {
	std::cerr << f.what() << std::endl;
}