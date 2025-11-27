#include "ogga/csvlog.hpp"

#include <deque>
#include <unordered_map>
#include <vector>

#include "ogga/print.hpp"

#include "ogga/scopetimer.hpp"

void csvlog_test() {
	std::cout << "################# csvlog Test #################" << "\n\n";
	std::filesystem::remove_all("csvlog");

	ogga::csvlog minutelyLog(ogga::csvlog::minutely("csvlog/minutelyLogs"), "status", "message");
	minutelyLog.log("INFO", "It's Alive!");
	minutelyLog.log("WARNING", "Nah just kidding.");

	ogga::csvlog hourlyLog(ogga::csvlog::hourly("csvlog/hourlyLogs"), "status", "message");
	hourlyLog.log("INFO", "It's Alive!");
	hourlyLog.log("WARNING", "Nah just kidding.");

	ogga::csvlog dailyLog(ogga::csvlog::daily("csvlog/dailyLogs"), "status", "message");
	dailyLog.log("INFO", "It's Alive!");
	dailyLog.log("WARNING", "Nah just kidding.");

	ogga::csvlog monthlyLog(ogga::csvlog::monthly("csvlog/monthlyLogs"), "status", "message");
	monthlyLog.log("INFO", "It's Alive!");
	monthlyLog.log("WARNING", "Nah just kidding.");

	ogga::csvlog regularlog("csvlog/regularLogs/regularLog.csv", "status", "message");
	regularlog.log("INFO", "It's Alive!");
	regularlog.log("WARNING", "Nah just kidding.");

	auto matches = ogga::csvlog::getMatches("csvlog/regularLogs/regularLog.csv", "status", "WARNING");
	for (auto& e : matches) {
		std::cout << e << "\n";
	}
	std::cout << "\n";

	std::cout << "Check /bin/csv_log" << "\n";

	std::cout << "\n################# csvlog Test #################" << "\n";
}
