#include "ogga/csvlog.hpp"

#include <deque>
#include <unordered_map>
#include <vector>

#include "ogga/print.hpp"

#include "ogga/scopetimer.hpp"

void csvlog_test() {
	std::cout << "################# csvlog Test #################" << "\n\n";
	ogga::csv_log minutelyLog(ogga::csv_log::minutely("csv_log/minutelyLogs"), "status", "message");
	minutelyLog.log("INFO", "It's Alive!");
	minutelyLog.log("WARNING", "Nah just kidding.");

	ogga::csv_log hourlyLog(ogga::csv_log::hourly("csv_log/hourlyLogs"), "status", "message");
	hourlyLog.log("INFO", "It's Alive!");
	hourlyLog.log("WARNING", "Nah just kidding.");

	ogga::csv_log dailyLog(ogga::csv_log::daily("csv_log/dailyLogs"), "status", "message");
	dailyLog.log("INFO", "It's Alive!");
	dailyLog.log("WARNING", "Nah just kidding.");

	ogga::csv_log monthlyLog(ogga::csv_log::monthly("csv_log/monthlyLogs"), "status", "message");
	monthlyLog.log("INFO", "It's Alive!");
	monthlyLog.log("WARNING", "Nah just kidding.");

	ogga::csv_log regularlog("csv_log/regularLogs/regularLog.csv", "status", "message");
	regularlog.log("INFO", "It's Alive!");
	regularlog.log("WARNING", "Nah just kidding.");

	std::cout << "Check /bin/csv_log" << "\n";

	std::cout << "\n################# csvlog Test #################" << "\n";
}
