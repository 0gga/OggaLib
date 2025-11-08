#include <deque>
#include <vector>

#include "ogga/print.hpp"

void printTest() {
	std::cout << "################# print Test #################" << "\n\n";
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
	int* intptr = new int(1);

	std::string string{"\nString: string"};
	constexpr char charArr[] = "\nconst char[] -> const char*";
	ogga::print("Int: ", 1, "\nDouble: ", 1.1, "\nInt* address: ", intptr, charArr, string, "\nchar: ", 'c');
	ogga::print("Vector: ", vector, '\n', "Deque:  ", deque);
	delete intptr;
	std::cout << "\n################# print Test #################" << "\n";
}
