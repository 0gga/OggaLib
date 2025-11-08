#include <deque>

#include "print.hpp"

int main() {
	std::vector<int> vector;
	for (int i = 0; i < 10;) {
		vector.push_back(++i);
	}

	int int10[10];
	std::deque<int> deque;
	for (int i = 0; i < 10;) {
		*int10 = ++i;
		deque.push_back(*int10);
	}
	ogga::print("Vector: ", vector, '\n', "Deque:  ", deque);

	return 0;
}
