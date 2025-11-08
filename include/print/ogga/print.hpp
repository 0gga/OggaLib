#pragma once
#include <cstring>

#include "ogga/element_type.hpp"
#include <iostream>
#include <type_traits>

namespace ogga {
	template<typename T>
	constexpr void stream_one(std::ostream& os, const T& value, bool newline = false, bool inContainer = false) noexcept {
		if constexpr (std::is_convertible_v<T, const char*> || (!std::is_pointer_v<T> && requires { os << value; }))
			os << value;
		else if constexpr (std::is_pointer_v<std::decay_t<decltype(value)>>) {
			if (!value) {
				os << "nullptr";
				return;
			}
			if (inContainer)
				stream_one(os, *value);
			else
				os << static_cast<const void*>(value);
		} else if constexpr (requires { value.first, value.second; }) {
			os << '(';
			stream_one(os, value.first);
			os << ", ";
			stream_one(os, value.second);
			os << ')';
		} else if constexpr (requires { std::begin(value); std::end(value); }) {
			os << "[ ";
			for (auto it = value.begin(); it != value.end(); ++it) {
				if (it != std::begin(value))
					newline ? os << ",\n  " : os << ", ";
				stream_one(os, *it, newline, true);
			}
			os << " ]";
		} else {
			os << "[unsupported type]";
		}
	}

	template<typename First, typename... Rest>
	constexpr void print(First&& first, Rest&&... rest) noexcept {
		bool newline{false};

		auto process = [&](auto&& arg) {
			if constexpr (std::is_convertible_v<std::decay_t<decltype(arg)>, const char*>) {
				const size_t len = std::strlen(arg);
				if (len >= 2 && arg[len - 2] == '%' && arg[len - 1] == 'n') {
					std::string_view s(arg);
					std::cout << s.substr(0, len - 2);
					newline = true;
					return;
				}
			}
			if constexpr (requires { std::begin(arg); std::end(arg); })
				stream_one(std::cout, arg, newline);
			else
				stream_one(std::cout, arg, false);
			newline = false;
		};
		(process(std::forward<First>(first)), ..., process(std::forward<Rest>(rest)));
		std::cout << std::endl;
	}
}
