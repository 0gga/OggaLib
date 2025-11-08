#pragma once
#include "element_type.hpp"
#include <iostream>
#include <type_traits>

namespace ogga {
	template<typename T>
	constexpr void stream_one(std::ostream& os, const T& value) noexcept {
		if constexpr (requires { os << value; })
			os << value;
		else if constexpr (std::is_pointer_v<T> && std::is_arithmetic_v<std::remove_pointer<T>>)
			os << *value;
		else if constexpr (requires { std::begin(value); std::end(value); }) {
			os << "[ ";
			for (auto it = value.begin(); it != value.end(); ++it) {
				if (it != std::begin(value))
					os << ", ";
				if constexpr (std::is_pointer_v<std::decay<decltype(*it)>>)
					os << **it;
				else
					os << *it;
			}
			os << " ]";
		} else {
			os << "[unsupported type]";
		}
	}

	template<typename... Args>
	constexpr void print(Args&&... args) noexcept {
		(stream_one(std::cout, args), ...);
		std::cout << std::endl;
	}
}
