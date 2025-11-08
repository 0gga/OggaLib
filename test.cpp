#ifdef OGGA_DEV

void print_test();
void scopetimer_test();
void stopwatch_test();

int main() {
	print_test();
	//scopetimer_test();
	//stopwatch_test();

	return 0;
}

#else
int main() {
	return 0;
}
#endif
