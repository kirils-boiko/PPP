
/*	Try This exercise from p792:
*	The emphatically not recommended version of a program that copies from input to output;
*	This version guesses the size of the input buffer allowing the potential overflow;
*/

#include <iostream>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>

constexpr int max_size = 100;

int main()
// quick and dirty dictionary
{
	std::string from, to;
	std::cin >> from >> to;				// get source and target file names

	std::ifstream is{ from };				// open input stream
	std::ofstream os{ to };					// open output stream

	std::istream_iterator<std::string> ii{ is };		// make input iterator for stream
	std::istream_iterator<std::string> eos;				// input sentinel
	std::ostream_iterator<std::string> oo{ os, "\n" };	// make output iterator for stream

	std::vector<std::string> b{ max_size };				// b is a vector of size max_size
	std::copy(ii, eos, b.begin());						// copy buffer to output

	for (int i = 0; i < b.size(); i++)
		os << b[i] << std::endl;

}