
/*	A simple text editor implementation using lists as the main data structure;
*	Assumptions:
*		A text document fits in the computer's main memory;
*		
* 
*	Five things that the in-memory representation supports:
*		1. Construction from a stream of bytes from input
*		2. Insertion of one or more characters
*		3. Deletion of one or more characters
*		4. Searching for a string
*		5. Generation of a stream of bytes for output to a file or screen
* 
*	Text document is represented as a list of lines, list<Line>, where a Line is a vector<char>;
*	Line representation relies on newline indicators (e.g., '\n') in user input;
*	A document is represented as an object of class Document;	
* 
*	For searching, a simple non-optimal algorithm is used:
*		1. Find the first character of the search string in the document
*		2. See if that character and the following characters match the search string;
*		3. If so, return an iterator to the string's first character; 
			if not, look for the next occurrence of that first character;
		4. If occurrence is not found, return an iterator to the end of the sequence;
*/

#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <regex>
#include <iostream>

using Line = std::vector<char>;				// a line is a vector of characters
class Text_iterator {
	// keep track of line and character position within a line
	// purpose of the iterator is to visit the characters one after another ignoring the line break
	std::list<Line>::iterator line_pos;
	Line::iterator char_pos;

public:
	// start the iterator at line ll's character position pp:
	Text_iterator(std::list<Line>::iterator ln_iter, Line::iterator ch_iter)
		:line_pos{ ln_iter }, char_pos{ ch_iter } {}

	char& operator*() { return *char_pos; }
	Text_iterator& operator++();
	bool operator==(const Text_iterator& other) const {
		return line_pos == other.line_pos && char_pos == other.char_pos;
	}
	bool operator!=(const Text_iterator& other) const {
		return !(*this == other);
	}

};

struct Document {
	std::list<Line> line_lst;				// a document is a list of Lines
	Document() { line_lst.push_back(Line{}); }

	Text_iterator begin() {					// first character of first line
		return Text_iterator(line_lst.begin(), (*line_lst.begin()).begin());
	}
	Text_iterator end() {					// one beyond the last character of the last line
		auto last_line = line_lst.end();	// iterator pointing to the one beyond the last line
		--last_line;						// we know that there is at least one empty line
		return Text_iterator(last_line, (*last_line).end());
	}
};

std::istream& operator>>(std::istream& is, Document& d)
{
	for (char ch; is.get(ch); ) {
		d.line_lst.back().push_back(ch);		// add the character
		if (ch == '\n')
			d.line_lst.push_back(Line{});		// add another line
	}
	if (d.line_lst.back().size())				// if the last line is not empty
		d.line_lst.push_back(Line{});			// add final empty line
	return is;
}


Text_iterator& Text_iterator::operator++()
{
	++char_pos;								// proceed to the next character
	if (char_pos == (*line_pos).end()) {
		++line_pos;							// proceed to the next line
		char_pos = (*line_pos).begin();		// bad if ln==line.end(); so make sure it isn't
	}
	return *this;
}

void print(Document& d)
{
	for (auto p : d)
		std::cout << p;
}

void erase_line(Document& d, int n)
{
	if (n < 0 || d.line_lst.size() - 1 <= n)
		return;
	auto p = d.line_lst.begin();
	std::advance(p, n);
	d.line_lst.erase(p);
}

template<typename Iterator>
bool match(Iterator first, Iterator last, const std::string& s)
{
	for (int i = 0; s[i]; i++) {
		if (first == last || *first != s[i])
			return false;
		++first;
	}
	return true;
}

Text_iterator find_txt(Text_iterator first, Text_iterator last, const std::string& s)
{
	if (s.size() == 0)
		return last;				// can't find an empty string
	char first_char = s[0];
	while (true) {
		auto p = std::find(first, last, first_char);
		if (p == last || match(p, last, s))
			return p;
		first = ++p;				// look at the next character
	}
}

int main()
{
	Document doc;
	std::cin >> doc;
	print(doc);

	auto p = find_txt(doc.begin(), doc.end(), "damn");
	if (p == doc.end())
		std::cout << "not found" << std::endl;
	else
		print(doc);
}

// custom implementation of the standard library function advance()
//template<typename Iterator>
//void advance(Iterator& p, int n) {
//	whlle (0 < n) { ++p; --n; }
//}

//// custom implementaion of the standard library function advance() that can also move backwards
//template<typename Iterator>
//void advance(Iterator& p, int n) {
//	while (n > 0) {
//		++p; --n;
//	}
//	while (n < 0) {
//		--p; ++n;
//	}
//}