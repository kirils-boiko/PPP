/*	Chapter 20: Drill Exercises
*/

#include <vector>
#include <list>
#include <iostream>
#include <algorithm>

constexpr int maxsize = 10;

template<typename T>
void print_array(const T* p, int maxsize)
{
	std::cout << "{ ";
	for (int i = 0; i < maxsize; i++)
		std::cout << p[i] << " ";
	std::cout << '}' << std::endl;
}

template<typename T>
void print_container(const T container)
{
	std::cout << "{ ";
	for (auto elem : container)
		std::cout << elem << " ";
	std::cout << '}' << std::endl;
}

template<typename Iter1, typename Iter2>
	// requirese Input_operator<Iter1>() && Output_operator<Iter2>()
Iter2 copyx(Iter1 f1, Iter1 e1, Iter2 f2)
{
	if (f1 == e1)
		return f2;
	for (auto i = f1; i != e1; ++i) {
		*f2 = *i;
		++f2;
	}
	return f2;
}

int main()
{
	int int_array[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	std::vector<int> int_vector{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	std::list<int> int_list{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	print_array(int_array, maxsize);
	print_container(int_vector);
	print_container(int_list);

	int int_array_copy[maxsize];
	for (int i = 0; i < maxsize; i++)
		int_array_copy[i] = int_array[i];
	std::vector<int> int_vector_copy = int_vector;
	std::list<int> int_list_copy = int_list;

	print_array(int_array_copy, maxsize);
	print_container(int_vector_copy);
	print_container(int_list_copy);

	for (int i = 0; i < maxsize; i++)
		int_array_copy[i] += 2;
	for (int i = 0; i < int_vector_copy.size(); i++)
		int_vector_copy[i] += 3;
	for (auto& x : int_list_copy)
		x += 5;

	print_array(int_array_copy, maxsize);
	print_container(int_vector_copy);
	print_container(int_list_copy);

	copyx(int_array_copy, int_array_copy + maxsize, int_vector_copy.begin());
	copyx(int_list_copy.begin(), int_list_copy.end(), int_array_copy);
	
	print_array(int_array_copy, maxsize);
	print_container(int_vector_copy);
	print_container(int_list_copy);

	int value_to_find = 3;
	auto pos = std::find(int_vector_copy.begin(), int_vector_copy.end(), value_to_find);
	if (pos != int_vector_copy.end())
		std::cout << "The value " << value_to_find << " is found at int_vector_copy["
		<< pos - int_vector_copy.begin() << ']' << std::endl;
	else
		std::cout << "The value " << value_to_find << " is not found" << std::endl;
}

