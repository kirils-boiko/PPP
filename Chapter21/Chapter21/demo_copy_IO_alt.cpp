
/*	A simpler alternative to copying the input to output using a set rather than a vector 
*/

#include <iostream>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <string>
#include <set>

int main()
{
	std::string from, to;
	std::cin >> from >> to;			// get source and targer file names

	std::ifstream is{ from };			// make input stream
	std::ofstream os{ to };				// make output stream

	std::set<std::string> b{ std::istream_iterator<std::string>{is}, std::istream_iterator<std::string>{} };
	std::copy(b.begin(), b.end(), std::ostream_iterator<std::string>{os, " "});	// copy buffer to output
}