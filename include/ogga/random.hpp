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

		// Decide dist type based on (int || floating point)
		using dist_t = std::conditional_t<
			std::is_integral_v<T>,
			std::uniform_int_distribution<T>,
			std::uniform_real_distribution<T>
		>;

		dist_t dist(rangeBegin, rangeEnd);

		if constexpr (std::is_floating_point_v<T>) {
			T factor   = std::pow(10.0, decimalCount);
			return std::round(dist(global_rng()) * factor) / factor;
		}

		return dist(global_rng());
	}
}
