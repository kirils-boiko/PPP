
/*	Writing function alternatives for C-style strings using the dereference operator;
	*/

#include <iostream>

constexpr int max = 10;

char* strdupx(const char* s);
char* findx(const char*, const char*);
int strcmpx(const char* s1, const char* s2);


int main()
{
	char chArr[] = "Damn boy";
	char toFind[] = "mn";
	char toCmp[] = "Damn boyz";
	char* p = strdupx(chArr);

	std::cout << chArr << std::endl;
	std::cout << p << std::endl;

	char* f = findx(chArr, toFind);
	if (f)
		std::cout << f << std::endl;
	else
		std::cout << "not found" << std::endl;

	int result = strcmpx(chArr, toCmp);
	std::cout << result << std::endl;
	
}


char* strdupx(const char* s)
	// copy the C-style string into memory allocated on the free store
{
	int count;
	for (count = 0; *(s+count); count++)
		;
	
	char* p = new char[++count];
	for (int i = 0; i < count; i++)
		*(p+i) = *(s + i);

	return p;
}

char* findx(const char* s, const char* x)
// finds the first occurrence of the C-style str x in s, else return nullptr
{
	int i, j;
	for (i = 0; *(s + i); i++) {	// loop over the elements of the s array
		for (j = 0; *(x + j) && *(s + i + j) == *(x + j); j++)	// loop over the elements of the x array
			;
		if (*(x + j) == '\0')
			return const_cast<char*>(s + i);
	}
	return nullptr;
}

int strcmpx(const char* s1, const char* s2)
// compare two C-style str, return <0 if s1 < s2, >0 if s2 > s1, 0 if s1 == s2;
{
	int i = 0;
	while (*(s1 +i) && *(s2 + i)) {
		if (*(s1 + i) > *(s2 + i))
			return 1;
		else if (*(s1 + i) < *(s2 + i))
			return -1;
		i++;
	}

	if (*(s1 + i) == *(s2 + i))
		return 0;
	else if (*(s1 + i))
		return 1;
	else
		return -1;
}