
#include "vec02.h"

constexpr int sz = 10;

void print_some(vector<int>&);

int main()
{
	vector<int> vi;
	for (int i = 0; i < sz; i++) vi.push_back(i);
	vi.print();
	std::cout << std::endl;
	print_some(vi);
}

void print_some(vector<int>& v)
{
	int i = -1;
	while (std::cin >> i && i != -1)
	try {
		std::cout << "v[" << i << "] == " << v.at(i) << std::endl;
	}
	catch (out_of_range) {
		std::cout << "bad index: " << i << std::endl;
		}
}