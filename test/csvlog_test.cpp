#include "ogga/csvlog.hpp"

#include <deque>
#include <unordered_map>
#include <vector>

#include "ogga/print.hpp"

#include "ogga/scopetimer.hpp"

void csvlog_test() {
	std::cout << "################# csvlog Test #################" << "\n\n";
	ogga::csv_log dailyLog(ogga::csv_log::daily("dailyLogs"), "status", "message");
	ogga::csv_log regularlog("regularLogs/regularLog.csv", "status", "message");
	dailyLog.log("INFO", "It's Alive!");
	dailyLog.log("WARNING", "Nah just kidding.");
	regularlog.log("INFO", "It's Alive!");
	regularlog.log("WARNING", "Nah just kidding.");

	std::cout << "Check /bin/logs" << "\n";

	std::cout << "\n################# csvlog Test #################" << "\n";
}
