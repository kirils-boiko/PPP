
/*	Implementation of a simple symbol table using the template class Pair used
	to hold a pair of values of any type;
	*/

#include <iostream>
#include <vector>
#include <string>

template<class A, class B>
struct Pair {
	A first;
	B second;

	Pair(A a, B b)
		: first{ a }, second{ b } {}

};

template<class A, class B>
std::ostream& operator<<(std::ostream& os, Pair<A,B> pair) {
	return os << pair.first << ": " << pair.second;
}

int main() {
	Pair<std::string, std::string> name00{ std::string{"Name"}, std::string{"Kiro"} };
	Pair<std::string, std::string> name01{ std::string{"Name"}, std::string{"Gleb"} };
	Pair<std::string, std::string> name02{ std::string{"Name"}, std::string{"Max"} };

	Pair<std::string, int> age00{ std::string{"Age"}, int{ 22 } };
	Pair<std::string, int> age01{ std::string{ "Age" }, int{ 22 } };
	Pair<std::string, int> age02{ std::string{ "Age" }, int{ 21 } };

	std::vector<Pair<std::string, std::string>> names{ name00, name01, name02 };
	std::vector<Pair<std::string, int>> ages{ age00, age01, age02 };

	Pair<std::vector<Pair<std::string, std::string>>, std::vector<Pair<std::string, int>>> mainvec{ names, ages };

	if (mainvec.first.size() == mainvec.second.size())
		for (int i = 0; i < mainvec.first.size(); i++)
			std::cout << mainvec.first[i] << '\n' << mainvec.second[i] << '\n';
	std::cout << std::endl;

}

