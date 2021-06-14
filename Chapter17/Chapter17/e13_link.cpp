
/*
	A modified Link class that hold a value of struct God;
	struct God has members of type string: name, mythology, vehicle, and weapon;
	print_all() function lists gods with their attributes one per line;
	add_ordered() member function places its new element in its correct 
	lexicographical position;
	Using the Links with the values of type God, a list of three mythologies is made;
	Then, each list's elements are moved into the lexicographically ordered list;
	*/

#include <string>
#include <iostream>

struct God {
	std::string name{ "-" };
	std::string mythology{ "-" };
	std::string vehicle{ "-" };
	std::string weapon{ "-" };

	friend std::ostream& operator<<(std::ostream& os, const God& obj);
};

class Link {
public:
	God value;

	Link(God v, Link* p = nullptr, Link* s = nullptr)
		: value{ v }, prev{ p }, succ{ s } {}

	Link* insert(Link* n);				// insert n before this object
	Link* add(Link* n);					// insert n after this object
	Link* add_ordered(Link* n);			// insert n in lexicographical order
	Link* erase();						// remove this object from the list
	Link* copy();						// copy only this node
	Link* find(const std::string& s);	// find s in list
	const Link* find(const std::string& s) const;	// find s in const list
	Link* advance(int n) const;			// move n positions in list
	

	Link* next() const { return succ; }
	Link* previous() const { return prev; }

private:
	Link* prev;
	Link* succ;
};

void print_all(Link* p);



int main() {

	Link* norse_gods = new Link{ {"Magni", "Norse", "Horse Gullfaxi", "Mjolnir"} };
	norse_gods = norse_gods->insert(new Link{ {"Thor", "Norse", "Cart", "Lightning"} });
	norse_gods = norse_gods->insert(new Link{ {"Odin", "Norse", "Sleipnir", "Gungnir"} });
	norse_gods = norse_gods->insert(new Link{ {"Zeus", "Greek", "-", "Lightning"} });
	norse_gods = norse_gods->insert(new Link{ {"Freyja", "Norse", "Chariot", "Brisingamen"} });

	Link* greek_gods = new Link{ {"Hera", "Greek", "Chariot drawn by peacocks", "Pomegranate"} };
	greek_gods = greek_gods->insert(new Link{ {"Athena", "Greek", "-", "Spear"} });
	greek_gods = greek_gods->insert(new Link{ {"Mars", "Greek", "War chariot", "Spear"} });
	greek_gods = greek_gods->insert(new Link{ {"Poseidon", "Greek", "Horse", "Trident"} });

	// correct the name of Mars to Ares
	Link* p = greek_gods->find("Mars");
	if (p) p->value.name = "Ares";

	// put Zeus from norse_gods into the greek_gods
	p = norse_gods->find("Zeus");
	if (p) {
		if (p == norse_gods) norse_gods = p->next();
		p->erase();
		greek_gods = greek_gods->insert(p);
	}

	// print it all
	print_all(norse_gods);
	std::cout << std::endl;
	print_all(greek_gods);
	std::cout << std::endl;
	

	// creating two lexicographically sorted lists of Norse and Greek gods
	Link* greek_gods_sorted = nullptr;
	Link* norse_gods_sorted = nullptr;

	for (Link* pnorse = norse_gods; pnorse; pnorse = pnorse->next())
		norse_gods_sorted = norse_gods_sorted->add_ordered(pnorse->copy());
	for (Link* pgreek = greek_gods; pgreek; pgreek = pgreek->next())
		greek_gods_sorted = greek_gods_sorted->add_ordered(pgreek->copy());
	
	print_all(norse_gods_sorted);
	std::cout << std::endl;
	print_all(greek_gods_sorted);
	std::cout << std::endl;
}

std::ostream& operator<<(std::ostream& os, const God& obj)
{
	os << "{ " << obj.name << ", " << obj.mythology <<
		", " << obj.vehicle << ", " << obj.weapon << " }";
	return os;
}

Link* Link::insert(Link* n)				// insert n before p; return n
{
	Link* p = this;						// pointer to this object
	if (n == nullptr) return p;			// nothing to insert
	if (p == nullptr) return n;			// nothing to insert into
	n->succ = p;						// p comes as n successor
	if (p->prev) p->prev->succ = n;		// n becomes a successor of whatever the p was successor of
	n->prev = p->prev;					// n's predecessor becomes whatever the p's predecessor was
	p->prev = n;
	return n;
}

Link* Link::add(Link* n)				// insert n after this object		
// simplified through the implicit use of this
{
	if (this == nullptr) return n;
	if (n == nullptr) return this;
	n->prev = this;			// n comes after p
	if (succ)
		succ->prev = n;	// n becomes the predecessor of whatever was the successor of p
	n->succ = succ;		// n's successor becomes whatever was the p's successor
	succ = n;			// finally, p's successor becomes n
	return n;
}

Link* Link::add_ordered(Link* n)				// insert n in lexicographical position		
// assumes that the list is in correct lexicographical order
// returns a pointer to the newly added Link
{
	if (this == nullptr) return n;
	if (n == nullptr) return this;
	
	Link* p = this;
	while (p->previous())	// get to the beginning of the list
		p = p->previous();
	Link* beginning = p;
	while (n->value.name.compare(p->value.name) > 0) {
		if (p->next() == nullptr) {
			p->add(n);
			return beginning;
		}
		p = p->next();
	}

	// now insert n right after p
	p->insert(n);
	return beginning;
}

Link* Link::erase()					// remove this object from the list
{
	if (this == nullptr) return nullptr;
	if (succ) succ->prev = prev;
	if (prev) prev->succ = succ;
	return succ;
}

Link* Link::copy()					// copy only the current node
{
	if (this == nullptr) return nullptr;
	Link* temp = new Link{ value };
	return temp;
}

Link* Link::find(const std::string& s)	// find s in list
{
	Link* p = this;
	while (p) {
		if (p->value.name == s) return p;
		p = p->next();
	}
	return nullptr;
}

const Link* Link::find(const std::string& s) const	// find s in const list
{
	// empty for now
	return this;
}

Link* Link::advance(int n) const			// move n positions in list
{
	Link* p = const_cast<Link*>(this);
	if (p == nullptr) return nullptr;
	if (n > 0) {
		while (n--) {
			if (p->next() == nullptr) return nullptr;
			p = p->next();
		}
	}
	else if (n < 0) {
		while (n++) {
			if (p->previous() == nullptr) return nullptr;
			p = p->previous();
		}
	}
	return p;
}

void print_all(Link* p)
{
	while (p) {
		std::cout << p->value << std::endl;
		p = p->next();
	}
}