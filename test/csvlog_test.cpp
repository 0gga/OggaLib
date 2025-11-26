#include "ogga/csvlog.hpp"

#include <deque>
#include <unordered_map>
#include <vector>

#include "ogga/print.hpp"

#include "ogga/scopetimer.hpp"

void csvlog_test() {
	std::cout << "################# csvlog Test #################" << "\n\n";
	ogga::csv_log log(ogga::csv_log::daily("logs"), "status", "message");
	log.log("INFO", "It's Alive!");

	std::cout << "Check /bin/logs" << "\n";

	std::cout << "\n################# csvlog Test #################" << "\n";
}
