
/* Eto russkij drill using templates */

#include <string>
#include <iostream>
#include <iomanip>
#include <vector>

constexpr int width = 12;
constexpr int max = 10;

template<typename T>
struct S {
private:
	T val;
	
public:
	explicit S(T var)
		: val{ var } {}
	T& get();
	const T& get() const;
	//void set(const T&);

	S<T>& operator=(const T&);

};

template<typename T> T& S<T>::get() { return val; }
template<typename T> const T& S<T>::get() const { return val; }
//template<typename T> void S<T>::set(const T& t) { val = t; }
template<typename T> S<T>& S<T>::operator=(const T& arg)
{
	val = arg;
	return *this;
}

template<typename T> std::ostream& operator<<(std::ostream& os, std::vector<T> vv)
{
	os << "{ ";
	for (int i = 0; i < vv.size(); i++)
		os << vv[i] << ' ';
	return os << '}';
}

template<typename T> std::istream& operator>>(std::istream& is, std::vector<T>& vv)
{
	char ch;
	is >> ch;
	if (ch != '{') {
		is.unget();
		return is;
	}

	for (T val; is >> val; ) {
		vv.push_back(val);
		is >> ch;
		if (ch != ',' && ch != '}') {
			is.unget();
			is.setstate(std::ios_base::failbit);
			return is;
		}
		if (ch == '}')
			return is;
	}

	return is;
}

template<typename T> 
void read_val(T& val)
{
	std::cin >> val;
	if (!std::cin)
		std::cerr << "error: read failure;" << std::endl;
	return;
}


int main()
{
	S<int> myInt{ 100 };
	S<char> myChar{ 'K' };
	S<double> myDouble{ 123.456 };
	S<std::string> myStr{ "Kiro" };
	const S<std::string> constStr{ "Boiko" };
	S<std::vector<int>> myVec{ std::vector<int>(max, 0) };

	std::cout << std::setw(width) << "myInt: " << myInt.get() << std::endl;
	std::cout << std::setw(width) << "myChar: " << myChar.get() << std::endl;
	std::cout << std::setw(width) << "myDouble: " << myDouble.get() << std::endl;
	std::cout << std::setw(width) << "myStr: " << myStr.get() << std::endl;
	std::cout << std::setw(width) << "constStr: " << constStr.get() << std::endl;
	std::cout << std::setw(width) << "myVec: " << "{ ";
	for (int i = 0; i < max; i++)
		std::cout << myVec.get()[i] << " ";
	std::cout << "}" << std::endl;

	myStr = "Kirils";
	std::cout << std::setw(width) << "upd myStr: " << myStr.get() << std::endl;

	myChar = 'O';
	std::cout << std::setw(width) << "upd myChar: " << myChar.get() << std::endl;

	std::cout << "Enter a character: ";
	char ch;
	read_val(ch);
	myChar = ch;
	
	std::cout << "Enter an int: ";
	int ii;
	read_val(ii);
	myInt = ii;

	std::cout << "Enter a double: ";
	int dd;
	read_val(dd);
	myDouble = dd;

	std::cout << "Enter a string: ";
	std::string str;
	read_val(str);
	myStr = str;

	std::cout << "Enter a vector of ints (in { val, val, ...} format): ";
	std::vector<int> vi;
	read_val(vi);
	S<std::vector<int>> sv{ vi };

	std::cout << std::setw(width) << "myChar: " << myChar.get() << std::endl;
	std::cout << std::setw(width) << "myInt: " << myInt.get() << std::endl;
	std::cout << std::setw(width) << "myDouble: " << myDouble.get() << std::endl;
	std::cout << std::setw(width) << "myStr: " << myStr.get() << std::endl;
	std::cout << std::setw(width) << "myVec: " << "{ ";
	for (int i = 0; i < sv.get().size(); i++)
		std::cout << sv.get()[i] << " ";
	std::cout << "}" << std::endl;
}