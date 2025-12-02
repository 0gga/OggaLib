#pragma once
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

namespace ogga {
	class csvlog {
	public:
		template<typename... Args>
		explicit csvlog(const std::string& filepath, Args&&... headers);

		template<typename... Args>
		void log(Args&&... fields);

		static std::vector<std::string> getMatches(const std::string& filePath, const std::string& column, const std::string& field);

		static std::string minutely(const std::string& dir = "logs") {
			return minute_filename(dir);
		}

		static std::string hourly(const std::string& dir = "logs") {
			return hour_filename(dir);
		}

		static std::string daily(const std::string& dir = "logs") {
			return day_filename(dir);
		}

		static std::string monthly(const std::string& dir = "logs") {
			return month_filename(dir);
		}

	private: // Member Variables
		std::ofstream out;
		size_t columnCount;

	private: // Member Functions
		static std::string minute_filename(const std::string& dir) {
			using namespace std::chrono;

			const auto now         = system_clock::now();
			const auto currentDate = floor<days>(now);
			const year_month_day ymd{currentDate};

			std::string time = now_timestamp();

			int year        = static_cast<int>(ymd.year());
			unsigned month  = static_cast<unsigned>(ymd.month());
			unsigned day    = static_cast<unsigned>(ymd.day());
			unsigned hour   = static_cast<unsigned>(std::stoi(time.substr(0, 2)));
			unsigned minute = static_cast<unsigned>(std::stoi(time.substr(3, 2)));

			char buf[64];
			std::snprintf(buf, sizeof(buf), "%s/%04d-%02u-%02u_%02u-%02u.csv", dir.c_str(), year, month, day, hour, minute);

			return buf;
		}

		static std::string hour_filename(const std::string& dir) {
			using namespace std::chrono;

			const auto now         = system_clock::now();
			const auto currentDate = floor<days>(now);
			const year_month_day ymd{currentDate};

			std::string time = now_timestamp();

			int year       = static_cast<int>(ymd.year());
			unsigned month = static_cast<unsigned>(ymd.month());
			unsigned day   = static_cast<unsigned>(ymd.day());
			unsigned hour  = static_cast<unsigned>(std::stoi(time.substr(0, 2)));

			char buf[64];
			std::snprintf(buf, sizeof(buf), "%s/%04d-%02u-%02u_%02u.csv", dir.c_str(), year, month, day, hour);

			return buf;
		}

		static std::string day_filename(const std::string& dir) {
			using namespace std::chrono;

			const auto now         = system_clock::now();
			const auto currentDate = floor<days>(now);
			const year_month_day ymd{currentDate};

			int year       = static_cast<int>(ymd.year());
			unsigned month = static_cast<unsigned>(ymd.month());
			unsigned day   = static_cast<unsigned>(ymd.day());

			char buf[64];
			std::snprintf(buf, sizeof(buf), "%s/%04d-%02u-%02u.csv", dir.c_str(), year, month, day);

			return buf;
		}

		static std::string month_filename(const std::string& dir) {
			using namespace std::chrono;

			const auto now         = system_clock::now();
			const auto currentDate = floor<days>(now);
			const year_month_day ymd{currentDate};

			int year       = static_cast<int>(ymd.year());
			unsigned month = static_cast<unsigned>(ymd.month());

			char buf[64];
			std::snprintf(buf, sizeof(buf), "%s/%04d-%02u.csv", dir.c_str(), year, month);

			return buf;
		}

		static std::string now_timestamp() {
			using namespace std::chrono;

			auto now = system_clock::now();
			auto t   = system_clock::to_time_t(now);
			int ms   = duration_cast<milliseconds>(now.time_since_epoch()).count() % 100;

			std::tm tm{};
#ifdef _WIN32
			localtime_s(&tm, &t);
#else
			localtime_r(&tm, &tm);
#endif

			char buf[32];
			std::strftime(buf, sizeof(buf), "%H:%M:%S", &tm);

			char msbuf[3];
			std::snprintf(msbuf, sizeof(msbuf), "%02d", ms);
			return std::string(buf) + "." + std::string(msbuf);
		}

		static size_t detectHeaderColumnCount(const std::filesystem::path& p) {
			std::ifstream in(p);
			if (!in)
				return 0;

			std::string header;
			if (!std::getline(in, header))
				return 0;

			size_t count = 1;
			for (const char c : header)
				if (c == ',')
					count++;
			return count;
		}

		template<typename... Args>
		void writeHeader(Args&&... headers) {
			writeRow(std::forward<Args>(headers)...);
		}

		template<typename... Args>
		void writeRow(Args&&... fields) {
			bool first{true};
			((out << (first ? (first = false, "") : ",") << escape(fields)), ...);
			out << "\n";
		}

		static std::string escape(const std::string_view s) {
			std::string out = "\"";
			for (char c : s)
				if (c == '"')
					out += "\"\"";
				else
					out += c;

			out += "\"";
			return out;
		}

		static std::string escape(const std::string& s) {
			return escape(std::string_view(s));
		}

		template<typename T>
		static std::string escape(const T& value) {
			if constexpr (std::is_arithmetic_v<T>)
				return escape(std::to_string(value));
			else if constexpr (std::is_convertible_v<T, std::string_view>)
				return escape(std::string_view(value));
			else
				static_assert(!sizeof(T), "csvlog: unsupported field type. Must be arithmetic or convertible to string_view.");
		}
	};

	template<typename... Args>
	csvlog::csvlog(const std::string& filepath, Args&&... headers) {
		std::filesystem::path p(filepath);

		if (!p.parent_path().empty())
			std::filesystem::create_directories(p.parent_path());

		bool exists = std::filesystem::exists(p);
		bool empty  = exists ? std::filesystem::file_size(p) == 0 : true;

		const size_t expectedColumnCount = sizeof...(Args) + 1;

		if (exists && !empty) {
			if (expectedColumnCount != detectHeaderColumnCount(p))
				throw(std::runtime_error("csvlog: existing file header column count does not match CTOR header count."));
		}

		out.open(p, std::ios::app);
		if (!out)
			throw std::runtime_error("csvlog: failed to open file" + p.string());

		columnCount = sizeof...(Args) + 1;

		static_assert(sizeof...(Args) > 0, "At least one column is required in csvlog");
		if (!exists || empty)
			writeHeader("timestamp", std::forward<Args>(headers)...);
	}

	template<typename... Args>
	void csvlog::log(Args&&... fields) {
		if (sizeof...(Args) + 1 != columnCount)
			throw std::runtime_error("csvlog: field count does not match header count.");
		writeRow(now_timestamp(), std::forward<Args>(fields)...);
		out.flush();
	}

	inline std::vector<std::string> csvlog::getMatches(const std::string& filePath, const std::string& column, const std::string& field) {
		std::ifstream in(filePath);
		if (!in)
			throw std::runtime_error("csvlog: failed to open file: " + filePath);

		std::string line;

		if (!std::getline(in, line))
			return {};

		std::vector<std::string> headers;
		{
			std::string current;
			bool inQuotes = false;

			for (char c : line) {
				if (c == '"') {
					inQuotes = !inQuotes;
				} else if (c == ',' && !inQuotes) {
					headers.push_back(current);
					current.clear();
				} else {
					current.push_back(c);
				}
			}
			headers.push_back(current);
		}

		int targetCol = -1;
		for (size_t i = 0; i < headers.size(); ++i) {
			if (headers[i] == column) {
				targetCol = static_cast<int>(i);
				break;
			}
		}
		if (targetCol == -1)
			throw std::runtime_error("csvlog: column: " + column + " not found");

		std::vector<std::string> matches;

		while (std::getline(in, line)) {
			std::vector<std::string> fields;

			std::string current;
			bool inQuotes = false;

			for (char c : line) {
				if (c == '"') {
					inQuotes = !inQuotes;
				} else if (c == ',' && !inQuotes) {
					fields.push_back(current);
					current.clear();
				} else {
					current.push_back(c);
				}
			}
			fields.push_back(current);

			if (targetCol < static_cast<int>(fields.size())) {
				if (fields[targetCol] == field) {
					matches.push_back(line);
				}
			}
		}

		return matches;
	}
}
