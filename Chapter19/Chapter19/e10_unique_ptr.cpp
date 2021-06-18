
/*	Simple unique_ptr implementation supporting a constructor, destructor,
*	->, *, and release();
*/

#include <algorithm>
#include <iostream>
#include <vector>

constexpr int maxsz = 10;

template<typename T>
class Unique_ptr {
	T* p;

public:
	Unique_ptr(T* ptr)
		:p{ ptr } {}
	~Unique_ptr() { delete p; }

	T& operator*() { return *p; }
	T* operator->() const { return p; }
	
	T* release() {
		T* temp = nullptr;
		std::swap(temp, p);
		return temp;
	}
};

int main()
{
	Unique_ptr<int> pi{ new int{10} };
	Unique_ptr<std::vector<int>> pvi{ new std::vector<int> };

	for (int i = 0; i < maxsz; i++)
		pvi->push_back(i);

	std::cout << "i == " << *pi << std::endl;

	std::cout << "vi == { ";
	for (int i = 0; i < pvi->size(); i++)
		std::cout << (*pvi)[i] << ' ';
	std::cout << '}' << std::endl;

}