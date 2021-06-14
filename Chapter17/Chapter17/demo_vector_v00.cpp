
/*
	Very simplified vector of doubles (like vector<double>)
	*/

class vector {
	int sz;			// the size
	double* elem;	// pointer to the first element (of type double)
public:
	vector(int s);	// constructor: allocate s doubles,
					// let eleme point to them
					// store s in sz;
	int size() const { return sz; }		// the current size
};

vector::vector(int s)
	: sz{ 0 }, elem{ nullptr } {}


int main()
{

}