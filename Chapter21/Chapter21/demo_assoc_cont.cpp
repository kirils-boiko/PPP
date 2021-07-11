

/*	Making a list of the number of occurrences of words in a text using
	the associative container called map;
	It is done by keeping a list of words seen so far with the number of times each
	word has been encountered in a text;
	If the word has been seen, its count is incremented by one, else, the word
	is inserted in a list and is given a value of 1;
*/

#include <map>
#include <string>
#include <iostream>


int main()
{
	std::map<std::string, int> words;			// keep (word,frequency) pairs

	for (std::string s; std::cin >> s; )
		++words[s];								// note: words is subscripted by a string
												// note: if you subscript an unknown word, a new (key, value)
												//	pair is created with the default value for int of 0

	for (const auto& p : words)
		std::cout << p.first << ": " << p.second << '\n';
}