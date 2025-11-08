#pragma once
#include <string>
#include <chrono>

namespace ogga {
	class stopwatch {
	public:
		stopwatch() noexcept : start_(clock_t::now()) {}

		void start() noexcept;
		void stop() noexcept;
		void reset() noexcept;

		[[nodiscard]] std::string hours() const noexcept;
		[[nodiscard]] std::string minutes() const noexcept;
		[[nodiscard]] std::string seconds() const noexcept;
		[[nodiscard]] std::string milliseconds() const noexcept;
		[[nodiscard]] std::string microseconds() const noexcept;
		[[nodiscard]] std::string nanoseconds() const noexcept;

	private:
		using clock_t = std::chrono::steady_clock;
		clock_t::time_point start_;
		clock_t::time_point stopped_;

		template<typename T>
		[[nodiscard]] std::string to_string(const char* suffix) const noexcept {
			auto duration = std::chrono::duration_cast<T>((stopped_ == clock_t::time_point{} ? clock_t::now() : stopped_) - start_).count();
			return std::to_string(duration) + suffix;
		}
	};

	inline void stopwatch::start() noexcept {
		if (stopped_ != clock_t::time_point{}) {
			start_ += clock_t::now() - stopped_;
			stopped_ = clock_t::time_point{};
		}
	}

	inline void stopwatch::stop() noexcept {
		stopped_ = clock_t::now();
	}

	inline void stopwatch::reset() noexcept {
		start_   = clock_t::now();
		stopped_ = clock_t::time_point{};
	}

	inline std::string stopwatch::hours() const noexcept {
		return to_string<std::chrono::hours>("h");
	}

	inline std::string stopwatch::minutes() const noexcept {
		return to_string<std::chrono::minutes>("min");
	}

	inline std::string stopwatch::seconds() const noexcept {
		return to_string<std::chrono::seconds>("s");
	}

	inline std::string stopwatch::milliseconds() const noexcept {
		return to_string<std::chrono::milliseconds>("ms");
	}

	inline std::string stopwatch::microseconds() const noexcept {
		return to_string<std::chrono::microseconds>("us");
	}

	inline std::string stopwatch::nanoseconds() const noexcept {
		return to_string<std::chrono::nanoseconds>("ns");
	}
}
