#include <iostream>

#include "ogga/stopwatch.hpp"

void stopwatch_test() {
	std::cout << "################# stopwatch Test #################" << "\n\n";
	ogga::stopwatch timer;
	for (int i{}; i < INT_MAX; i++);
	timer.stop();

	std::cout << timer.nanoseconds() << "\n";
	std::cout << timer.microseconds() << "\n";
	std::cout << timer.milliseconds() << "\n";
	std::cout << timer.seconds() << "\n";
	std::cout << "\n################# stopwatch Test #################" << "\n";
}
