#include <iostream>

#include "ogga/scopetimer.hpp"

void scopetimer_test() {
	std::cout << "################# scopetimer Test #################" << "\n\n";
	{
		ogga::scopetimer timer("compute", "ms");
		for (int i{}; i < INT_MAX; i++);
	}
	for (int i{}; i < INT_MAX / 10; i++);
	std::cout << "\n################# scopetimer Test #################" << "\n";
}
