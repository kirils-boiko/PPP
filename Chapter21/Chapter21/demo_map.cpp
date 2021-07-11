
/*	Dow Jones Index example using associative containters to store constituents' weights,
*	share prices, and company names;
*/

#include <map>
#include <string>
#include <iostream>
#include <utility>
#include <functional>

std::map<std::string, double> dow_price = {			// Dow Jones Industrial index (symbol, price);
	{"MMM", 81.86},
	{"AA", 34.69},
	{"MO", 54.45},
	//...
};

std::map<std::string, double> dow_weight = {		// Dow Jones Industrial index (symbol, weight);
	{"MMM", 5.8549},
	{"AA", 2.4808},
	{"MO", 3.8940},
	//...
};

std::map<std::string, std::string> dow_name = {			// Dow Jones Industrial index (symbol, name);
	{"MMM", "3M Co."},
	{"AA", "Alcoa Inc."},
	{"MO", "Altria Group Inc."},
	//...
};

double weighted_value(const std::pair<std::string, double>& a, const std::pair<std::string, double>& b)
	// extract values and multiply
{
	return a.second * b.second;
}

// Generalized six-argument numerical algorithm, inner_product()
template<typename In, typename In2, typename T, typename BinOp, typename BinOp2>
	// requires Input_Iterator<In> && Input_iterator<In2> && Number<T>
	//	&& Binary_operation<BinOp,T,Value_type<In>>()
	//	&& Binary_operation<BinOp2,T,Value_type<In2>>()
T inner_product(In first, In last, In2 first2, T init, BinOp op, BinOp2 op2)
{
	while (first != last) {
		init = op(init, op2(*first, *first2));
		++first;
		++first2;
	}
	return init;
}

int main()
{
	double alcoa_price = dow_price["AA"];			// read values from a map
	double alcoa_weight = dow_weight["AA"];

	if (dow_price.find("INTC") != dow_price.end())	// find an entry in a map
		std::cout << "Intel is in the DJI" << std::endl;

	// write price for each company in the Dow index by iterating through the map
	for (const auto& p : dow_price) {
		const std::string& symbol = p.first;			// the "ticker" symbol
		std::cout << symbol << '\t'
			<< p.second << '\t'
			<< dow_name[symbol] << std::endl;
	}

	double dji_index = inner_product(dow_price.begin(), dow_price.end(),		// all companies
		dow_weight.begin(),					// their weights
		0.0,								// initial accumulator value
		std::plus<double>(),				// accumulate by addition (as usual) 
		weighted_value);					// extract values and weights, and multiply

	std::cout << "The DJI value: " << dji_index << std::endl;
}
