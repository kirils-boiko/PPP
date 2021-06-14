
/* Drill Part 1: Arrays */


#include <iostream>
#include <cmath>
#include <iomanip>

constexpr int max = 10;
int ga[max];

void f(int[], int);
int factorial(int);

int main()
{
	std::cout << std::setw(15) << "ga: ";
	for (int i = 0; i < max; i++) {
		ga[i] = std::pow(2, i);
		std::cout << ga[i] << " ";
	}
	std::cout << std::endl;

	int la[max];
	for (int i = 0; i < max; i++) {
		la[i] = std::pow(3, i);
	}
	f(la, max);

	int aa[max];
	for (int i = 0; i < max; i++)
		aa[i] = factorial(i + 1);
	f(aa, max);
}

void f(int argArray[], int n)
{
	int la[max];
	std::cout << std::setw(15) << "f's la: ";
	for (int i = 0; i < max; i++) {
		la[i] = ga[i];
		std::cout << la[i] << " ";
	}
	std::cout << std::endl;

	int* freeArray = new int[n];
	std::cout << std::setw(15) << "f's freeArray: ";
	for (int i = 0; i < n; i++) {
		freeArray[i] = argArray[i];
		std::cout << freeArray[i] << " ";
	}
	std::cout << std::endl;
	
	delete[] freeArray;
}

int factorial(int n)
{
	return (n == 1 || n == 0) ? 1 : n * factorial(n - 1);
}