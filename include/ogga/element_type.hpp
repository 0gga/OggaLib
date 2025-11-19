#pragma once
#include "element_type.hpp"
#include <iostream>
#include <string>
#include <type_traits>

namespace ogga {
	template<typename T>
	struct element_type {
		using type = std::remove_cvref_t<T>;
	};

	template<typename T, std::size_t N>
	struct element_type<T[N]> {
		using type = std::remove_cvref_t<T>;
	};

	template<typename T, std::size_t N>
	struct element_type<std::array<T, N>> {
		using type = std::remove_cvref_t<T>;
	};

	template<typename T> requires requires { typename T::value_type; }
	struct element_type<T> {
		using type = std::remove_cvref_t<typename T::value_type>;
	};

	template<typename T>
	using element_type_t = element_type<T>::type;
}
