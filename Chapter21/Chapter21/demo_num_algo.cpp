
/*	Demonstrating four STL-style numerical algorithms that help you with numerical computations;
*/

#include <iostream>
#include <vector>
#include <list>
#include <functional>


//------------------------------------------------------------
// Basic three-argument numerical algorithm, accumulate()
template<typename In, typename T>
	// requirees Input_iterator<In>() && Number<T>()
T accumulate(In first, In last, T init)
	// adds a sequence of values; the type of result is the type of initial value;
{
	while (first != last) {
		init = init + *first;			// often called the accumulator
		++first;
	}
	return init;
}


//------------------------------------------------------------
// Generalized four-argument numerical algorithm, accumulate()
template<typename In, typename T, typename BinOp>
	//	generalized four-argument accumulate() version;
	//	any binary operation that accepts two arguments of accumulator's type can be used;
	//	requires Input_iterator<In>() && Number<T>()
	//		&& Binary_operator<BinOp, Value_type<In>, T>()
T accumulate(In first, In last, T init, BinOp op)
{
	while (first != last) {
		init = op(init, *first);
		++first;
	}
	return init;
}


//------------------------------------------------------------
// Basic four-argument numerical algorithm, inner_product()
template<typename In, typename In2, typename T>
	//	requires Input_iterator<In> && Input_iterator<In2>
	//		&& Number<T>
T inner_product(In first, In last, In2 first2, T init)
// note: this is the way we multiply two vectors (yielding a scalar)
{
	while (first != last) {
		init = init + (*first) * (*first2);		// multiply pairs of elements and accumulate
		++first;
		++first2;
	}
	return init;
}


//------------------------------------------------------------
// Generalized six-argument numerical algorithm, inner_product()
template<typename In, typename In2, typename T, typename BinOp, typename BinOp2>
	//	requires Input_iterator<In> && Input_Iterator<In2> && Number<T>
	//		&& Binary_operation<BinOp, T, Value_type<In>>()
	//		&& Binary_operation<BinOp, T< Value_type<In2>>()
T inner_product(In first, In last, In2 first2, T init, BinOp op, BinOp2 op2)
	//	op2 is used to do the binary operation between the elements pointed by two input operators (e.g., multiply)
	//	op is then used to do the binary operation on init (accumulator) and the result of op2 (e.g., accumulate)
{
	while (first != last) {
		init = op(init, op2(*first, *first2));
		++first;
		++first2;
	}
	return init;
}


struct Record {
	double unit_price;
	int units;		// number of units sold
};

struct Price {		// function object for accumulating the price 
	double operator()(double v, const Record& r) {
		return v + r.unit_price * r.units;
	}
};


int main()
{
	int a[] = { 1, 2, 3, 4, 5 };
	std::cout << "sum of array elements: " << accumulate(a, a + sizeof(a) / sizeof(int), 0) << std::endl;

	std::vector<double> vd(10, 10);
	double sum = accumulate(vd.begin(), vd.end(), 0.0);
	std::cout << "sum of vector elements: " << sum << std::endl;

	long long_sum = accumulate(vd.begin(), vd.end(), long{ 0 });		// accumulator flexibility
	int int_sum = accumulate(vd.begin(), vd.end(), int{ 0 });

	// example use of generalized four-argument accumulate with binary operation;
	//	std::multiplies<T> and std::divides<T> are examples of standard library function objects
	std::cout << "product of vector elements: " << accumulate(vd.begin(), vd.end(), 1.0, std::multiplies<double>()) << std::endl;
	std::cout << "quotient of vector elements: " << accumulate(vd.begin(), vd.end(), 1.0, std::divides<double>()) << std::endl;

	Record A{ 1.0, 70 };
	Record B{ 90.0, 10 };
	Record C{ 15.0, 10 };
	Record D{ 500.0, 2 };

	std::vector<Record> vr;
	vr.push_back(A);
	vr.push_back(B);
	vr.push_back(C);
	vr.push_back(D);

	std::cout << "Total value of products in stock: " << accumulate(vr.begin(), vr.end(), 0.0, Price()) << std::endl;


	// inner product for DIY stock index
	std::vector<double> diy_prices = { 400.72, 372.15, 242.73, 82.40, 601.28 };
	std::list<double> diy_weights = { 28.90, 23.40, 17.65, 16.67, 13.38 };
	
	double diy_index = inner_product(diy_prices.begin(), diy_prices.end(), diy_weights.begin(), 0.0);
	std::cout << "DIY Index value: " << diy_index << std::endl;
}