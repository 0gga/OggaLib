#include "ogga/random.hpp"

#include <iomanip>
#include <iostream>

void random_test() {
	std::cout << "################# Random Test #################" << "\n\n";

	const int intRandom       = ogga::random(1, 5);
	const double doubleRandom1 = ogga::random(1.0, 5.0, 2);
	const double doubleRandom2 = ogga::random(1.0, 5.0, 6);
	std::cout << "Random Integer 1 - 5: " << std::setprecision(15) << intRandom << std::endl;
	std::cout << "Random Double 1.0 - 5.0 with 2 decimals: " << std::setprecision(15) << doubleRandom1 << std::endl;
	std::cout << "Random Double 1.0 - 5.0 with 6 decimals: " << std::setprecision(15) << doubleRandom2 << std::endl;

	std::cout << "\n################# Random Test #################" << "\n";
}
