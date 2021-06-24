
/*	Code represenatation of the linked lists
*	The list class is not complete definition of the standard library list;
*	The purpose of list class it convey an understanding of what linked lists are;
*	The definitions for class list<Elem> are not provided - the code below is just a demonstration;
*/
//
//template<typename Elem>
//struct Link {
//	Link* prev;		// previous link
//	Link* succ;		// successor link
//	Elem val;		// the value
//};
//
//template<typename Elem>
//struct list {
//	Link<Elem>* first;
//	Link<Elem>* last;	// one beyond the last link
//};
//

//------------------------------------------------------------------
// List operations

#include <iostream>

template<typename Elem>
struct Link {
	Link* prev;		// previous link
	Link* succ;		// successor link
	Elem val;		// the value
};

template<typename Elem>
class list {
	// representation and implementation details

public:
	class iterator;									// member type: iterator

	iterator begin();								// iterator to first element
	iterator end();									// iterator to one beyond last element

	iterator insert(iterator p, const Elem& v);		// insert v into list after p
	iterator erase(iterator p);						// remove p from the list

	void push_back(const Elem& v);					// insert v at end
	void push_front(const Elem& v);					// insert v at front
	void pop_front();								// remove the first element
	void pop_back();								// remove the last element

	Elem& front();									// the first element
	Elem& back();									// the last element
};

template<typename Elem>
class list<Elem>::iterator {
	Link<Elem>* curr;								// current link

public:
	iterator(Link<Elem>* p)
		: curr{ p } {}
	
	iterator& operator++() { curr = curr->succ; return *this; }		// forward
	iterator& operator--() { curr = curr->prev; return *this; }		// backward
	Elem& operator*() { return curr->val; }							// get value (dereference)

	bool operator==(const iterator& b) const { return curr == b.curr; }
	bool operator!=(const iterator& b) const { return curr != b.curr; }
};

template<typename Iterator>
Iterator high(Iterator first, Iterator last)
// return an iterator to the element in [first, last) that has the highest value
{
	Iterator high = first;
	for (Iterator p = first; p != last; ++p)
		if (*high < *p) high = p;
	return high;
}

void f()
{
	list<int>lst;
	for (int x; std::cin >> x; )
		lst.push_front(x);

	list<int>::iterator p = high(lst.begin(), lst.end());
	if (p == lst.end())
		std::cout << "The list is empty";
	else
		std::cout << "the highest value was " << *p << '\n';
}
