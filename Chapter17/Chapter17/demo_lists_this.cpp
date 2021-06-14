
/* 
	Using the this pointer to improve and simplify our Link class by
	turning the supporting operations into the member functions*/

#include <string>
#include <iostream>

class Link {
public:
	std::string value;

	Link(const std::string& v, Link* p = nullptr, Link* s = nullptr)
		: value{ v }, prev{ p }, succ{ s } {}
	
	Link* insert(Link* n);				// insert n before this object
	Link* add(Link* n);					// insert n after this object
	Link* erase();						// remove this object from the list
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

	Link* norse_gods = new Link{ "Thor" };
	norse_gods = norse_gods->insert(new Link{ "Odin" });
	norse_gods = norse_gods->insert(new Link{ "Zeus" });
	norse_gods = norse_gods->insert(new Link{ "Freia" });

	Link* greek_gods = new Link{ "Hera" };
	greek_gods = greek_gods->insert(new Link{ "Athena" });
	greek_gods = greek_gods->insert(new Link{ "Mars" });
	greek_gods = greek_gods->insert(new Link{ "Poseidon" });

	// correct the name of Mars to Ares
	Link* p = greek_gods->find("Mars");
	if (p) p->value = "Ares";

	// put Zeus from norse_gods into the greek_gods
	p = norse_gods->find("Zeus");
	if (p) {
		if (p == norse_gods) norse_gods = p->next();
		p->erase();
		greek_gods = greek_gods->insert(p);
	}
	
	// if you put p->erase() after inserting p into greek_gods, this check
	//	will tell you what's wrong;
	if (norse_gods->next())
		std::cout << "Freia's successor is " << norse_gods->next()->value << std::endl;
	if (greek_gods->previous() == nullptr)
		std::cout << "Zeus's predecessor is NULLPTR" << std::endl;
	if (greek_gods->next())
		std::cout << "Zeus's successor is " << greek_gods->next()->value << std::endl;
	if (greek_gods->find("Poseidon")->previous() == nullptr)
		std::cout << "Poseidon's predecessor is NULLPTR" << std::endl;

	// print it all
	print_all(norse_gods);
	std::cout << std::endl;
	print_all(greek_gods);
	std::cout << std::endl;
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

Link* Link::erase()					// remove this object from the list
{
	if (this == nullptr) return nullptr;
	if (succ) succ->prev = prev;
	if (prev) prev->succ = succ;
	return succ;
}

Link* Link::find(const std::string& s)	// find s in list
{
	Link* p = this;
	while (p) {
		if (p->value == s) return p;
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
	std::cout << "{ ";
	while (p) {
		std::cout << p->value;
		if (p = p->next()) std::cout << ", ";
	}
	std::cout << " }";
}