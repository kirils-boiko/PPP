
/*	Palindromes are the words that are spelled the same from both ends;
*	In this example, to determine whether a word is a palindrome, we check
*	if the first word is the same as the last, then if the second word is the
*	same as the second to last, and so on until the middle is reached;
*/

#include <iostream>
#include <string>

bool is_palindrome(const std::string&);
bool is_palindrome(const char s[], int n);
std::istream& read_word(std::istream&, char*, int);
bool is_palindrome(const char*, const char*);



/* Testing is_palindrome() using string */
//int main()
//{
//	for (std::string s; std::cin >> s; ) {
//		std::cout << s << " is";
//		if (!is_palindrome(s)) std::cout << " not";
//		std::cout << " a palindrome" << std::endl;
//	}
//}

/* Testing is_palindrome() using arrays without overflowing it*/
//int main()
//{
//	constexpr int max = 128;
//	for (char s[max]; read_word(std::cin, s, max); ) {
//		std::cout << s << " is";
//		if (!is_palindrome(s)) std::cout << " not";
//		std::cout << " a palindrome" << std::endl;
//	}
//}

/* Testing is_palindrome() using pointers */
int main()
{
	constexpr int max = 128;
	for (char s[max]; read_word(std::cin, s, max); ) {
		std::cout << s << " is";
		if (!is_palindrome(&s[0], &s[std::strlen(s) - 1])) std::cout << " not";
		std::cout << " a palindrome" << std::endl;
	}
}

std::istream& read_word(std::istream& is, char* buffer, int max)
// read at most max-1 characters from s into buffer
{
	is.width(max);		// read at most max-1 characters in the next >>
	is >> buffer;		// read whitespace-terminated word, add zero after the last char into buffer
	return is;
}

/* Palindromes using string */
bool is_palindrome(const std::string& s)
{
	int first = 0;
	int last = s.length() - 1;
	while (first < last) {	// while haven't reached the middle
		if (s[first] != s[last])
			return false;
		++first;
		--last;
	}
	return true;
}

/* Palindromes using arrays */
bool is_palindrome(const char s[], int n)
{
	int first = 0;
	int last = n - 1;
	while (first < last) {	// while haven't reached the middle
		if (s[first] != s[last])
			return false;
		++first;
		--last;
	}
	return true;
}

/* Palindromes using pointers */
bool is_palindrome(const char* first, const char* last)
// first points to the first letter, last to the last letter
{
	while (first < last) {
		if (*first != *last) return false;
		first++;
		last--;
	}
	return true;
}