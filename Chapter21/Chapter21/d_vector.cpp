
/* Drill Part 1: Vector 
*/

#include <iostream>
#include <vector>
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

struct Name_erase {		// Predicate for erase_if
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

	std::vector<Item> vi;

	if (rfile.is_open()) {
		std::istream_iterator<Item> ii{ rfile };
		std::istream_iterator<Item> eos{};
		vi = std::vector<Item>{ ii, eos };

		rfile.close();
	}
	else
		throw std::ios_base::failure("cannot open file");

	std::sort(vi.begin(), vi.end(), Name_sort());
	std::cout << "vi sorted by name:" << std::endl;
	for (const auto& x : vi)
		std::cout << x << std::endl;

	std::cout << "================================" << std::endl;
	std::sort(vi.begin(), vi.end(), Id_sort());
	std::cout << "vi sorted by id:" << std::endl;
	for (const auto& x : vi)
		std::cout << x << std::endl;

	std::cout << "================================" << std::endl;
	std::sort(vi.begin(), vi.end(), Value_sort());
	std::cout << "vi sorted by value (desc):" << std::endl;
	for (int i = vi.size() - 1; i >= 0; i--)
		std::cout << vi[i] << std::endl;

	std::cout << "================================" << std::endl;
	vi.insert(vi.end() - 1, Item{ "horse shoe", 11, 12.34 });
	vi.insert(vi.end() - 1, Item{ "Canon S400", 12, 499.95 });
	std::sort(vi.begin(), vi.end(), Id_sort());
	std::cout << "vi sorted by id:" << std::endl;
	for (const auto& x : vi)
		std::cout << x << std::endl;

	std::cout << "================================" << std::endl;
	std::string name1, name2;
	std::cout << "Enter the names of 2 items to erase: " << std::endl;
	std::cin >> name1 >> name2;
	int erased = 0;


	auto it = std::remove_if(vi.begin(), vi.end(), Name_erase{ name1 });
	if (it != vi.end()) {
		vi.erase(it, vi.end());
		erased++;
	}

	auto it2 = std::remove_if(vi.begin(), vi.end(), Name_erase{ name2 });
	if (it2 != vi.end()) {
		vi.erase(it2, vi.end());
		erased++;
	}
	
	std::cout << "vi after the erasure by item's name:" << std::endl;
	for (const auto& x : vi)
		std::cout << x << std::endl;
	std::cout << "Items erased: " << erased << std::endl;
	

	std::cout << "================================" << std::endl;
	int id1, id2;
	std::cout << "Enter the IDs of 2 items to erase: " << std::endl;
	std::cin >> id1 >> id2;
	erased = 0;


	auto it3 = std::remove_if(vi.begin(), vi.end(), [id1](const Item& i) { return i.iid == id1; });
	if (it3 != vi.end()) {
		vi.erase(it3, vi.end());
		erased++;
	}

	auto it4 = std::remove_if(vi.begin(), vi.end(), [id2](const Item& i) { return i.iid == id2; });
	if (it4 != vi.end()) {
		vi.erase(it4, vi.end());
		erased++;
	}

	std::cout << "vi after the erasure by item's ID:" << std::endl;
	for (const auto& x : vi)
		std::cout << x << std::endl;
	std::cout << "Items erased: " << erased << std::endl;

}
catch (std::ios_base::failure& f) {
	std::cerr << f.what() << std::endl;
}