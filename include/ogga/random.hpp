#pragma once
#include <random>

namespace ogga {
	/// Inline function and thread_local for a single instantiation of rng
	inline std::mt19937& global_rng() {
		thread_local std::mt19937 gen(std::random_device{}());
		return gen;
	}

	template<typename T, typename Z>
	T random(Z rangeBegin, Z rangeEnd) {
		static_assert(std::is_arithmetic_v<T>, "T must be an arithmetic type");
		static_assert(std::is_arithmetic_v<Z>, "Range values must be an arithmetic type");

		// Decide dist type based on (int || floating point)
		using dist_t = std::conditional_t<
			std::is_integral_v<T>,
			std::uniform_int_distribution<T>,
			std::uniform_real_distribution<T>
		>;

		dist_t dist(rangeBegin, rangeEnd);
		return dist(global_rng());
	}
}
