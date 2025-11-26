#pragma once
#include <chrono>
#include <filesystem>
#include <fstream>
#include <string>

namespace ogga {
	class csv_log {
	public:
		template<typename... Args>
		explicit csv_log(const std::string& filepath, Args&&... headers);

		template<typename... Args>
		void log(Args&&... fields);

		static std::string daily(const std::string& dir = "logs") {
			return today_filename(dir);
		}

	private: // Member Variables
		std::ofstream out;
		size_t columnCount;

	private: // Member Functions
		static std::string today_filename(const std::string& dir) {
			using namespace std::chrono;

			const auto now         = system_clock::now();
			const auto currentDate = floor<days>(now);
			const std::chrono::year_month_day ymd{currentDate};

			int year       = static_cast<int>(ymd.year());
			unsigned month = static_cast<unsigned>(ymd.month());
			unsigned day   = static_cast<unsigned>(ymd.day());

			return dir + ("/" + std::to_string(year) + "-" +
				(month < 10 ? "0" : "") + std::to_string(month) + "-" +
				(day < 10 ? "0" : "") + std::to_string(day) + ".csv");
		}

		static std::string now_timestamp() {
			using namespace std::chrono;

			auto now = system_clock::now();
			auto t   = system_clock::to_time_t(now);
			auto ms  = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;

			std::tm tm{};
#ifdef _WIN32
			localtime_s(&tm, &t);
#else
			localtime_r(&tm, &t);
#endif

			char buf[20];
			std::strftime(buf, sizeof(buf), "%H:%M:%S", &tm);
			return std::string(buf) + "." + std::to_string(ms.count());
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
				static_assert(!sizeof(T), "csv_log: unsupported field type. Must be arithmetic or convertible to string_view.");
		}
	};

	template<typename... Args>
	csv_log::csv_log(const std::string& filepath, Args&&... headers) {
		std::filesystem::path p(filepath);

		if (!p.parent_path().empty())
			std::filesystem::create_directories(p.parent_path());

		bool exists = std::filesystem::exists(p);
		bool empty  = exists ? std::filesystem::file_size(p) == 0 : true;

		const size_t expectedColumnCount = sizeof...(Args) + 1;

		if (exists && !empty) {
			if (expectedColumnCount != detectHeaderColumnCount(p))
				throw(std::runtime_error("csv_log: existing file header column count does not match CTOR header count."));
		}

		out.open(p, std::ios::app);
		if (!out)
			throw std::runtime_error("csv_log: failed to open file" + p.string());

		columnCount = sizeof...(Args) + 1;

		static_assert(sizeof...(Args) > 0, "At least one column is required in csv_log");
		if (!exists || empty)
			writeHeader("timestamp", std::forward<Args>(headers)...);
	}

	template<typename... Args>
	void csv_log::log(Args&&... fields) {
		if (sizeof...(Args) + 1 != columnCount)
			throw std::runtime_error("csv_log: field count does not match header count.");
		writeRow(now_timestamp(), std::forward<Args>(fields)...);
	}
}
