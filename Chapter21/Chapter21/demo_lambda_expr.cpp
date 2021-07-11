
/*	Lambda expression can be though of as a shorthand notation for defining a function
*	object (a class with an operator()) and then immediately creating an object of it;
*	The following sort and find algorithms could be written using lambda expressions
*	as the predicates;
*/

#include <vector>
#include <algorithm>
#include <string>
#include <iostream>


struct Record {
	std::string name;		// standard string for ease of use
	char addr[24];			// old style to match database layout
	//...
};

void f(std::vector<double>& v, int x)
{
	auto p = std::find_if(v.begin(), v.end(), [x](double a) { return a > x; });
	if (p != v.end())
		std::cout << "value is found" << std::endl;
	else
		std::cout << "value is not found" << std::endl;
}

void print_records(const std::vector<Record>& v)
{
	std::cout << "{ ";
	for (int i = 0; i < v.size(); i++)
		std::cout << v[i].name << ' ';
	std::cout << '}' << std::endl;
}

int main()
{
	Record A{ "Ares", "3" };
	Record B{ "Zeus", "2" };
	Record C{ "Athena", "1" };
	Record D{ "Poseidon", "0" };
	std::vector<Record> vr;
	vr.push_back(A);
	vr.push_back(B);
	vr.push_back(C);
	vr.push_back(D);

	std::sort(vr.begin(), vr.end(), [](const Record& a, const Record& b) 
		{ return a.name < b.name; });							// sort by name
	print_records(vr);

	std::sort(vr.begin(), vr.end(), [](const Record& a, const Record& b)
		{return strncmp(a.addr, b.addr, 24) < 0; });			// sort by address
	print_records(vr);
}