
/*	Since we can represent the input and output streams as sequences, we can use
*	copy algorithm for "copy to output" and "copy from input";
*/

#include <iostream>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>

void f()
{
	std::ostream_iterator<std::string> oo{ std::cout };		// assigning to *oo is to write cout
	std::istream_iterator<std::string> ii{ std::cin };		// reading *ii is to read as string from cin

	*oo = "Hello, ";
	++oo;						// get ready for the next output operation
	*oo = "World!\n";

	std::string s1 = *ii;
	++ii;						// get ready for the next input operation
	std::string s2 = *ii;
}

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

	std::vector<std::string> b{ ii, eos };				// b is a vector initialized from input
	std::sort(b.begin(), b.end());							// sort the buffer
	std::unique_
		copy(b.begin(), b.end(), oo);						// copy buffer to output

	// Note: iterator eos is the stream iterator's representation of end of input; 
	//	when an istream reaches end of input (EOF), its istream iterator will equal the default istream_iterator(eos);
}