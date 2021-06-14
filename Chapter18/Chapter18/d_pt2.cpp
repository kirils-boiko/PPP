#include <iomanip>
#include <iostream>
#include <vector>
#include <cmath>

/* Drill Part 2: STD Vector */

std::vector<int> gv;
constexpr int max = 10;

void f(std::vector<int>);
int factorial(int);

int main()
{
	for (int i = 0; i < max; i++)
		gv.push_back(std::pow(2, i));
	f(gv);

	std::vector<int> vv;
	for (int i = 1; i < max + 1; i++)
		vv.push_back(factorial(i));
	f(vv);
		
}

void f(std::vector<int> v)
{
	std::vector<int> lv(v.size(), 0);
	lv = gv;

	std::cout << std::setw(10) << "gv: ";
	for (int i = 0; i < lv.size(); i++)
		std::cout << lv[i] << " ";
	std::cout << std::endl;

	std::cout << std::setw(10) << "f's lv: ";
	std::vector<int> lv2 = v;
	for (int i = 0; i < lv2.size(); i++)
		std::cout << lv2[i] << " ";
	std::cout << std::endl;
}

int factorial(int n)
{
	return (n == 0 || n == 1) ? 1 : n * factorial(n - 1);
}