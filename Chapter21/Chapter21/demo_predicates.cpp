
//--------------------------------------------------------
// Predicates on class members

#include <vector>
#include <string>
#include <algorithm>

struct Record {
	std::string name;		// standard string for ease of use
	char addr[24];			// old style to match database layout
	//...
};

struct Cmp_by_name {
	bool operator()(const Record& a, const Record& b) const {
		return a.name < b.name;
	}
};

struct Cmp_by_addr {
	// hides the ugly and error-prone representation of address: an
	//	array of 24 characters (not zero terminated)
	bool operator()(const Record& a, const Record& b) const {
		return strcmp(a.addr, b.addr, 24) < 0;
	}
};

int main()
{
	std::vector<Record> vr;

	// you might be willing to sort vr by name or by address using the Cmp_by_name
	//	or Cmp_by_addr function objects;
	std::sort(vr.begin(), vr.end(), Cmp_by_name());			// sort by name
	// ...
	std::sort(vr.begin(), vr.end(), Cmp_by_addr());			// sort by address
	// ...
}



