/*	Sequences of characters: differences in real code;
*	Illustrating the differences between four ways of storing the sequences of characters:
*	array of char, vector<char, list<char>, and string;
*	The comparison function uses the iterator as the main concept;
* 
*	Note: iterators are available for vector<char>, list<char> and string; for array of chars,
*	the pointers are used instead;
*/

#include <vector>
#include <list>
#include <string>
#include <iostream>

constexpr int maxsize = 1000;

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

void f(char arg[])
{
	unsigned int count = 0;
	for (char* p = arg; *p != '\0'; p++)
		++count;
	std::cout << "Number of characters in the passed array of characters: " << count << std::endl;

	char hello[] = "Hello";
	std::cout << "The passed array of characters ";
	if (!strcmp(arg, hello))
		std::cout << "is";
	else
		std::cout << "is not";
	std::cout << " equivalent to 'Hello'" << std::endl;

	char howdy[] = "Howdy";
	if (strcmp(arg, howdy) < 0)
		std::cout << "The passed array of characters comes first in the dictionary, then 'Howdy'" << std::endl;
	else if (strcmp(arg, howdy) > 0)
		std::cout << "'Howdy' comes first in the dictionary, then the passed array of characters" << std::endl;
	else
		std::cout << "'Howdy' and the passed array of characters are equivalent" << std::endl;

	char copy[maxsize];
	int i;
	for (i = 0; arg[i] != '\0'; i++)
		copy[i] = arg[i];
	copy[i] = '\0';

	std::cout << "Array of characters copy: " << copy << std::endl;
		
}

template<typename container>
void f(container arg)
{
	std::cout << "Number of characters in the passed string: " << arg.size() << std::endl;

	container hello{ 'H', 'e', 'l', 'l', 'o' };
	std::cout << "The passed string ";
	if (arg == hello)
		std::cout << "is";
	else
		std::cout << "is not";
	std::cout << " equivalent to 'Hello'" << std::endl;

	container howdy{ 'H', 'o', 'w', 'd', 'y' };
	if (arg < howdy)
		std::cout << "The passed string comes first in the dictionary, then 'Howdy'" << std::endl;
	else if (arg > howdy)
		std::cout << "'Howdy' comes first in the dictionary, then the passed string" << std::endl;
	else
		std::cout << "'Howdy' and the passed string are equivalent" << std::endl;

	container copy{ arg };
}

int main()
{
	char hello_arr[] = "Hello";
	std::string hello_str = "Hello";
	std::vector<char> hello_vec{ 'H', 'e', 'l', 'l', 'o'};
	std::list<char> hello_list{ 'H', 'e', 'l', 'l', 'o'};

	std::cout << hello_arr << std::endl;
	std::cout << hello_str << std::endl;

	f(hello_arr);

}