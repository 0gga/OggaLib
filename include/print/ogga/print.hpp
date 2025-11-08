#pragma once
#include <charconv>
#include <cstring>

#include "ogga/element_type.hpp"
#include <iostream>
#include <type_traits>

namespace ogga {
	template<typename T>
	[[gnu::always_inline]] constexpr void stream_one(std::ostream& os, const T& value, bool newline = false, bool inContainer = false) noexcept {
		if constexpr (std::is_convertible_v<T, const char*> ||
			std::is_array_v<T> && std::is_same_v<std::remove_extent<T>, char>) {
			os.write(value, static_cast<std::streamsize>(std::strlen(value)));
		} else if constexpr (std::is_same_v<T, std::string_view> || std::is_same_v<T, std::string> ||
			std::is_same_v<element_type<T>, char> && requires { value.data(); value.size(); }) {
			os.write(value.data(), static_cast<std::streamsize>(value.size()));
		} else if constexpr (std::is_same_v<std::remove_cv_t<T>, char>
			|| std::is_same_v<std::remove_cv_t<T>, signed char>
			|| std::is_same_v<std::remove_cv_t<T>, unsigned char>) {
			os.put(static_cast<char>(value));
		} else if constexpr (!std::is_pointer_v<T> && requires { os << value; }) { /// Literals
			char buf[64];
			if constexpr (std::is_floating_point_v<T>) {
				auto [ptr, ec] = std::to_chars(std::begin(buf), std::end(buf), value, std::chars_format::general);
				if (ec == std::errc{})
					os.write(buf, ptr - buf);
				else
					os << value;
			} else {
				auto [ptr, ec] = std::to_chars(std::begin(buf), std::end(buf), value);
				if (ec == std::errc{})
					os.write(buf, ptr - buf);
				else
					os << value;
			}
		} else if constexpr (std::is_same_v<T, bool>) { /// Bool
			os.write(value ? "true" : "false", value ? 4 : 5);
		} else if constexpr (std::is_pointer_v<std::decay_t<decltype(value)>>) { /// Container
			if (!value) {
				os.write("nullptr", 7);
				return;
			}
			if (inContainer)
				stream_one(os, *value);
			else
				os << static_cast<const void*>(value);
		} else if constexpr (requires { value.first, value.second; }) {
			os.put('(');
			stream_one(os, value.first);
			os.write(", ", 2);
			stream_one(os, value.second);
			os.put(')');
		} else if constexpr (requires { std::begin(value); std::end(value); }) {
			os.write("[ ", 2);
			for (auto it = value.begin(); it != value.end(); ++it) {
				if (it != std::begin(value))
					newline ? os.write(",\n  ", 4) : os << ", ";
				stream_one(os, *it, newline, true);
			}
			os.write(" ]", 2);
		} else {
			os.write("[unsupported type]", 18);
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
		std::cout.put('\n');
	}
}
