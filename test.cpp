#ifdef OGGA_DEV
#include <iostream>

void print_test();
void scopetimer_test();
void stopwatch_test();
void thread_pool_test();

int main() {
	print_test();

	return 0;
}

#else
int main() {
	return 0;
}
#endif
