
/* Drill Part 1: List
*/

#include <iostream>
#include <list>
#include <string>
#include <fstream>
#include <iterator>
#include <stdexcept>
#include <algorithm>

struct Item {
	std::string name;
	int iid;
	double value;
};

std::istream& operator>>(std::istream& is, Item& item)
{
	is >> item.iid;
	if (is.eof())
		return is;

	char ch;
	is >> ch;
	if (ch != ':')
		throw std::ios_base::failure("input format error");


	is >> item.name;
	is >> ch;
	if (ch != ',')
		throw std::ios_base::failure("input format error");


	is >> item.value;
	is >> ch;
	if (ch != ';')
		throw std::ios_base::failure("input format error");

	return is;
}

std::ostream& operator<<(std::ostream& os, const Item& item)
{
	return os << item.iid << ": " << item.name << " , " << item.value;
}

struct Name_sort {		// Comparison function object to sort items by name
	bool operator()(const Item& x, const Item& y) const
	{
		return x.name < y.name;
	}
};

struct Id_sort {		// Comparison function object to sort items by id
	bool operator()(const Item& x, const Item& y) const
	{
		return x.iid < y.iid;
	}
};

struct Value_sort {		// Comparison function object to sort items by id
	bool operator()(const Item& x, const Item& y) const
	{
		return x.value < y.value;
	}

};

struct Name_erase {		// Predicate for erase_if by item's name
	std::string name;

	bool operator()(const Item& i)
	{
		return i.name == name;
	}
};

int main()
try {
	std::string from;
	std::cin >> from;

	std::ifstream rfile;
	rfile.open(from);

	std::list<Item> li;

	if (rfile.is_open()) {
		std::istream_iterator<Item> ii{ rfile };
		std::istream_iterator<Item> eos{};
		li = std::list<Item>{ ii, eos };

		rfile.close();
	}
	else
		throw std::ios_base::failure("cannot open file");

	li.sort(Name_sort());
	std::cout << "li sorted by name:" << std::endl;
	for (const auto& x : li)
		std::cout << x << std::endl;

	std::cout << "================================" << std::endl;
	li.sort(Id_sort());
	std::cout << "li sorted by id:" << std::endl;
	for (const auto& x : li)
		std::cout << x << std::endl;

	std::cout << "================================" << std::endl;
	li.sort(Value_sort());
	std::cout << "li sorted by value (desc):" << std::endl;
	for (auto p = li.rbegin(); p != li.rend(); ++p)
		std::cout << *p << std::endl;

	std::cout << "================================" << std::endl;
	li.insert(li.begin(), Item{ "horse shoe", 11, 12.34 });
	li.insert(li.end(), Item{ "Canon S400", 12, 499.95 });
	li.sort(Id_sort());
	std::cout << "li sorted by id:" << std::endl;
	for (const auto& x : li)
		std::cout << x << std::endl;

	std::cout << "================================" << std::endl;
	std::string name1, name2;
	std::cout << "Enter the names of 2 items to erase: " << std::endl;
	std::cin >> name1 >> name2;
	int erased = 0;


	auto it = std::remove_if(li.begin(), li.end(), Name_erase{ name1 });
	if (it != li.end()) {
		li.erase(it, li.end());
		erased++;
	}

	auto it2 = std::remove_if(li.begin(), li.end(), Name_erase{ name2 });
	if (it2 != li.end()) {
		li.erase(it2, li.end());
		erased++;
	}

	std::cout << "li after the erasure by item's name:" << std::endl;
	for (const auto& x : li)
		std::cout << x << std::endl;
	std::cout << "Items erased: " << erased << std::endl;


	std::cout << "================================" << std::endl;
	int id1, id2;
	std::cout << "Enter the IDs of 2 items to erase: " << std::endl;
	std::cin >> id1 >> id2;
	erased = 0;


	auto it3 = std::remove_if(li.begin(), li.end(), [id1](const Item& i) { return i.iid == id1; });
	if (it3 != li.end()) {
		li.erase(it3, li.end());
		erased++;
	}

	auto it4 = std::remove_if(li.begin(), li.end(), [id2](const Item& i) { return i.iid == id2; });
	if (it4 != li.end()) {
		li.erase(it4, li.end());
		erased++;
	}

	std::cout << "li after the erasure by item's ID:" << std::endl;
	for (const auto& x : li)
		std::cout << x << std::endl;
	std::cout << "Items erased: " << erased << std::endl;

}
catch (std::ios_base::failure& f) {
	std::cerr << f.what() << std::endl;
}