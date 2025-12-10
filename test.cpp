#ifdef OGGA_DEV

void csvlog_test();
void print_test();
void random_test();
void scopetimer_test();
void stopwatch_test();

int main() {
	//csvlog_test();
	print_test();
	//random_test();
	//scopetimer_test();
	//stopwatch_test();

	return 0;
}

#else
int main() {
	return 0;
}
#endif
