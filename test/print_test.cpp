#include <deque>
#include <unordered_map>
#include <vector>

#include "ogga/print.hpp"

void print_test() {
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
	std::unordered_map<int, std::string> map;
	constexpr int mapSize{3};
	for (int i = 0; i < mapSize; i++) {
		map[i] = std::to_string(mapSize - 1 - i);
	}

	int* intptr = new int(3);

	std::string string{"\nString: string"};
	constexpr char charArr[] = "const char[] -> const char*";

	ogga::print("Int: ", 1, "\nDouble: ", 1.1, "\nInt* ref: ", intptr, "\nInt* deref: ", *intptr);
	ogga::print(charArr, string, "\nchar: ", 'c');
	ogga::print("Vector<literals>: ", vector, '\n', "Deque<int*>: ", deque);
	ogga::print("pair: ", std::pair<char, std::string>('a', "bcd"));
	ogga::print("unordered_map with %n:  \n%n", map);

	delete intptr;
	std::cout << "\n################# print Test #################" << "\n";
}
