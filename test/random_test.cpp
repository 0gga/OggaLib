#include "ogga/random.hpp"

#include <iostream>

void random_test() {
	std::cout << "################# Random Test #################" << "\n\n";
	const double random = ogga::random(1.2, 1.5);
	std::cout << random << std::endl;
	std::cout << "\n################# Random Test #################" << "\n";
}
