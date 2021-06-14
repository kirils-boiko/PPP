
/* 
	A function void to_lower(char* s) that replaces all uppercase characters
	in a C-style string s with their lowercase equivalents;
	C-style string is a zero-terminated array of characters;
	*/

#include <iostream>

void to_lower(char* s);
char* strdupx(const char*);
char* findx(const char* s, const char* x);

int main() {
	/*
	std::cout << "Size of an int: " << sizeof(int) << std::endl;
	std::cout << "Size of a double: " << sizeof(double) << std::endl;
	std::cout << "Size of a bool: " << sizeof(bool) << std::endl;
	*/
	
	char cs[] = "DAMNBOY COWBOY";
	to_lower(cs);
	char tofind[] = "boy";

	char* p = strdupx(cs);

	std::cout << cs << std::endl;
	std::cout << p << std::endl;

	delete[] p;

	p = findx(cs, tofind);

	std::cout << p << std::endl;
}

void to_lower(char* s)	// lower all characters in a C-style string
{
	while (*s != '\0') {
		if (*s >= 'A' && *s <= 'Z')
			*s = *s + 'a' - 'A';
		s++;
	}
}

char* strdupx(const char* s)	// copy a C-style string into memory allocated on the free store
{
	int size = 0;
	while (s[size++])
		;

	char *p = new char[size];
	for (int i = 0; i < size; i++)
		p[i] = s[i];
	return p;
}

char* findx(const char* s, const char* x)	// find the 1st occurrence of C-style x in s
{
	int i;
	
	for (i = 0; s[i] != '\0'; i++) {
		int j;
		for (j = 0; s[i + j] == x[j]; j++)
			;
		if (x[j] == '\0') return const_cast<char*>(s + i);
	}

	return nullptr;
}