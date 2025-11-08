#include <iostream>

#include "stopwatch.hpp"

int main() {
	ogga::stopwatch timer;
	for (int i{}; i < INT_MAX; i++);
	timer.stop();

	std::cout << timer.nanoseconds() << "\n";
	std::cout << timer.microseconds() << "\n";
	std::cout << timer.milliseconds() << "\n";
	std::cout << timer.seconds() << "\n";

	return 0;
}
