#pragma once
#include <random>

namespace ogga {
	/// Inline function and thread_local for a single instantiation of rng
	inline std::mt19937& global_rng() {
		thread_local std::mt19937 gen(std::random_device{}());
		return gen;
	}

	template<typename T>
	auto random(T rangeBegin, T rangeEnd, const int decimalCount = 2) {
		static_assert(std::is_arithmetic_v<T>, "Range values must be an arithmetic type");

		if constexpr (std::is_integral_v<T>) {
			std::uniform_int_distribution<T> dist(rangeBegin, rangeEnd);
			return dist(global_rng());
		}

		std::uniform_real_distribution<double> dist(static_cast<double>(rangeBegin), static_cast<double>(rangeEnd));

		const double value   = dist(global_rng());
		const double factor  = std::pow(10.0, decimalCount);
		const double rounded = std::round(value * factor) / factor;
		return static_cast<T>(rounded);
	}
}
