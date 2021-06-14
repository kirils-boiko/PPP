
/* 
	Lists are among the most common and useful data structures;
	Usually, it's made out of links where each link holds some info and
	pointers to other links;
	*/

#include <iostream>
#include <string>

// An example of defining the doubly-linked list
// Note: a nullptr indicates that a link doesn't have a predecessor
//	or a successor (yet);
struct Link {
 	std::string value;
	Link* prev;
	Link* next;
	Link(const std::string& v, Link* p = nullptr, Link* s = nullptr)
		: value{ v }, prev{ p }, next{ s } { std::cout << "Link is created\n"; }
	~Link() {
		std::cout << "Link for \"" << value << "\" is destroyed\n";
		delete next;
	}
};


Link* insert(Link* p, Link* n);
Link* add(Link* p, Link* n);
Link* erase(Link* p);
Link* find(Link* p, const std::string& s);
Link* advance(Link* p, int n);
void print_all(Link* p);


/*	v00: obscure code
int main() {
	// Example of building a list of Norse gods;
	// Note: Freia as the predecessor of Odin who is a predecessor of Thor;

	Link* norse_gods = new Link{ "Thor", nullptr, nullptr };
	norse_gods = new Link{ "Odin", nullptr, norse_gods };
	norse_gods->next->prev = norse_gods;
	norse_gods = new Link{ "Freia", nullptr, norse_gods };
	norse_gods->next->prev = norse_gods;
}
*/


/* v01: improved version; uses insert operation
int main() {
	Link* norse_gods = new Link{ "Thor" };
	norse_gods = insert(norse_gods, new Link{ "Odin" });
	norse_gods = insert(norse_gods, new Link{ "Freia" });

	std::cout << "First came " << norse_gods->value << std::endl;
	std::cout << "Who created " << norse_gods->next->value << std::endl;
	std::cout << "Who created " << norse_gods->next->next->value << std::endl;

	delete norse_gods;

}
*/

/* v02: building two lists with newly added operations; */
int main() {
	Link* norse_gods = new Link{ "Thor" };
	norse_gods = insert(norse_gods, new Link{ "Odin" });
	norse_gods = insert(norse_gods, new Link{ "Zeus" });
	norse_gods = insert(norse_gods, new Link{ "Freia" });

	Link* greek_gods = new Link{ "Hera" };
	greek_gods = insert(greek_gods, new Link{ "Athena" });
	greek_gods = insert(greek_gods, new Link{ "Mars" });
	greek_gods = insert(greek_gods, new Link{ "Poseidon" });

	// Name of Greek god of war is Ares, not Mars; fixing that:
	Link* p = find(greek_gods, "Mars");
	if (p) p->value = "Ares";

	// Zeus is a greek god rather than a Norse god, fixing that:
	p = find(norse_gods, "Zeus");
	if (p) {
		if (p == norse_gods) norse_gods = p->next;	// to avoid erasing the top node
		erase(p);
		greek_gods = insert(greek_gods, p);
	}

	print_all(norse_gods);
	print_all(greek_gods);
}

// Supporting operations that the Link class needs in order to avoid
//	pointer fiddling for its users:
//		insert: insert before an element;
//		add: insert after an element;
//		erase: remove an element;
//		find: find a Link with a given value;
//		advance: get the nth successor;

// insert operation for hiding the tedious and error-prone pointer fiddling
// accounts for cases such as n, p, or p->prev == nullptr
// insert: insert n before p
Link* insert(Link* p, Link* n) 
{
	if (n == nullptr) return p;
	if (p == nullptr) return n;
	n->next = p;			// p comes after n
	if (p->prev)			// if not a nullptr
		p->prev->next = n;	// n with updated successor (p) comes after what used to be p's predecessor
	n->prev = p->prev;		// p's predecessor becomes n's predecessor
	p->prev = n;			// n becomes p's predecessor
	return n;
}

// add: insert n after p; return n;
Link* add(Link* p, Link* n) 
{
	if (p == nullptr) return n;
	if (n == nullptr) return p;
	n->prev = p;			// n comes after p
	if (p->next)
		p->next->prev = n;	// n becomes the predecessor of whatever was the successor of p
	n->next = p->next;		// n's successor becomes whatever was the p's successor
	p->next = n;			// finally, p's successor becomes n
	return n;
}

// erase: remove *p from list; return p's successor
Link* erase(Link* p)
{
	if (p == nullptr) return nullptr;
	if (p->prev) p->next->prev = p->prev;
	if (p->next) p->prev->next = p->next;
	return p->next;
}

// find: find s in list; return nullptr if not found
Link* find(Link* p, const std::string& s)
{
	while (p) {
		if (p->value == s) return p;
		p = p->next;
	}
	return nullptr;
}

// advance: move n position in list; return nullptr if not found;
//	positive n moves forward, negative - backward
Link* advance(Link* p, int n)
{
	if (p == nullptr) return nullptr;
	if (n > 0) {
		while (n--) {
			if (p->next == nullptr) return nullptr;
			p = p->next;
		}
	} else if (n < 0) {
		while (n++) {
			if (p->prev == nullptr) return nullptr;
			p = p->prev;
		}
	}
	return p;
}

void print_all(Link* p)
{
	std::cout << "{";
	while (p) {
		std::cout << p->value;
		if (p = p->next) std::cout << ", ";
	}
	std::cout << "}" << std::endl;
}