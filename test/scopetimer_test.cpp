#include <iostream>

#include "ogga/scopetimer.hpp"

void scopetimer_test() {
	std::cout << "################# scopetimer Test #################" << "\n\n";
	{
		ogga::scopetimer timer("compute");
		for (int i{}; i < INT_MAX; i++);
	}
	std::cout << "\n################# scopetimer Test #################" << "\n";
}
