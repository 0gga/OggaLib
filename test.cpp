#ifdef OGGA_DEV
#include <iostream>

void printTest();
void scopetimerTest();
void stopwatchTest();
void thread_poolTest();

int main() {
	printTest();

	return 0;
}

#else
int main() {
	return 0;
}
#endif
