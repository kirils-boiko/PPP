/* 
	List of gods example from demo_lists_this.cpp written using a
	singly-linked list (i.e., the prev member is left out);
	*/



	/*
		Using the this pointer to improve and simplify our Link class by
		turning the supporting operations into the member functions*/

#include <string>
#include <iostream>

class Link {
public:
	std::string value;

	Link(const std::string& v, Link* s = nullptr)
		: value{ v }, succ{ s } {}

	Link* insert(Link* n);				// insert n after this object
	Link* insert_beg(Link* n);			// insert n at the beginning of list
	void insert_end(Link* n);			// insert n at the end of list
	Link* erase_next();						// remove this object from the list
	Link* find_next(const std::string& s);	// find s in list
	const Link* find(const std::string& s) const;	// find s in const list
	Link* advance(unsigned int n) const;			// move n positions in list

	Link* next() const { return succ; }

private:
	Link* succ;
};

void print_all(Link* p);



int main() {

	Link* norse_gods = new Link{ "Freia" };
	norse_gods->insert_end(new Link{ "Zeus" });
	norse_gods->insert_end(new Link{ "Odin" });
	norse_gods->insert_end(new Link{ "Thor" });

	Link* greek_gods = new Link{ "Poseidon" };
	greek_gods->insert_end(new Link{ "Mars" });
	greek_gods->insert_end(new Link{ "Athena" });
	greek_gods->insert_end(new Link{ "Hera" });

	// correct the name of Mars to Ares
	Link* p = greek_gods->find_next("Mars");
	if (p->next()) p->next()->value = "Ares";

	// put Zeus from norse_gods into the greek_gods

	p = norse_gods->find_next("Zeus");
	if (p->next()) {
		p = p->erase_next();
		greek_gods = greek_gods->insert_beg(p);
	}

	// print it all
	print_all(norse_gods);
	std::cout << std::endl;
	print_all(greek_gods);
	std::cout << std::endl;
}


Link* Link::insert(Link* n)				// insert n after p; return n
{
	if (n == nullptr) return this;		// nothing to insert
	if (this == nullptr) return n;		// nothing to insert into
	n->succ = succ;
	succ = n;							// p comes as n successor
	return n;
}

Link* Link::insert_beg(Link* n)		// insert n at the beginning
{
	if (n == nullptr) return this;
	if (this == nullptr) return n;
	n->succ = this;
	return n;
}

void Link::insert_end(Link* n)			// insert n to the end of the list;
{
	if (n == nullptr) return;
	if (this == nullptr) return;
	Link* p = this;
	while (p->next())
		p = p->next();
	n->succ = p->next();
	p->succ = n;
	return;
}

Link* Link::erase_next()				// remove next object from the list
// return a pointer to this object;
{
	if (this == nullptr || succ == nullptr) return nullptr;
	Link* p = succ;
	succ = succ->next();
	return p;
}

Link* Link::find_next(const std::string& s)	// find s in list;
// return a p which next() points to s;
// assuming that this pointer points to the beginning of the list;
{
	Link* p = this;
	while (p->next()) {
		if (p->next()->value == s) return p;
		p = p->next();
	}
	return nullptr;
}

const Link* Link::find(const std::string& s) const	// find s in const list
{
	// empty for now
	return this;
}

Link* Link::advance(unsigned int n) const		// move n positions in list
{
	Link* p = const_cast<Link*>(this);
	if (p == nullptr) return nullptr;
	while (n--) {
		if (p->next() == nullptr) return nullptr;
		p = p->next();
	}
	return p;
}

void print_all(Link* p)
{
	std::cout << "{ ";
	while (p) {
		std::cout << p->value;
		if (p = p->next()) std::cout << ", ";
	}
	std::cout << " }";
}