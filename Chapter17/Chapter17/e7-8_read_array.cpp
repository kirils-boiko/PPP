
/*
	Program that reads characters from cin into an array that is allocated
	on the free store;
	Read individual characters until an exclamation mark is reached;
	*/

#include <iostream>
#include <string>

const int N_ELEMENTS = 10000;		// max characters to be entered


/* Reading an array of character using the C-style string array
int main()
{
	int i = 0;
	char* str = new char[N_ELEMENTS];
	for (char ch; std::cin.get(ch) && i < N_ELEMENTS; i++) {
		if (ch == '!')
			break;
		str[i] = ch;
	}
	str[i] = '\0';

	std::cout << str << std::endl;

	delete[] str;
}
	*/

/* Reading an array of characters through cin using the std::string */
int main()
{
	std::string str;
	
	for (char ch; std::cin.get(ch); ) {
		if (ch == '!')
			break;
		str.append(1, ch);
	}
	
	std::cout << str << std::endl;
}
