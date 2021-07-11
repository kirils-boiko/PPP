
/*	You can think of a set as a map where we are not interested in a value;
*/

#include <string>
#include <iostream>
#include <set>

struct Fruit {
	std::string name;
	int count;
	double unit_price;
};

struct Fruit_order {	// function object for less-than comparison
	bool operator()(const Fruit& a, const Fruit& b) const
	{
		return a.name < b.name;
	}
};


int main()
{
	std::set<Fruit, Fruit_order> inventory;

	inventory.insert(Fruit{ "apple", 5, 0.49 });
	inventory.insert(Fruit{ "orange", 10, 0.79 });

	for (auto p = inventory.begin(); p != inventory.end(); ++p)
		std::cout << "{ " << p->name << ',' << p->count << ',' << p->unit_price << " }" << std::endl;
}


