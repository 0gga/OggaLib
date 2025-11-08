#pragma once
#include <string>
#include <chrono>

#include "ogga/stopwatch.hpp"

namespace ogga {
	class scopetimer {
	public:
		scopetimer(std::string_view id, std::string_view suffix) noexcept;
		~scopetimer() noexcept;

	private:
		stopwatch timer_;
		std::ostream* os_;
		std::string id_;
		std::string suffix_;
	};

	inline scopetimer::scopetimer(std::string_view id, std::string_view suffix = "ns") noexcept
	: id_(id), suffix_(suffix), os_(&std::cout) {
		timer_.start();
	}

	inline scopetimer::~scopetimer() noexcept {
		try {
			timer_.stop();
			*os_ << id_ << ": ";
			*os_ << (suffix_ == "ns"
						 ? timer_.nanoseconds()
						 : suffix_ == "us"
							   ? timer_.microseconds()
							   : suffix_ == "ms"
									 ? timer_.milliseconds()
									 : suffix_ == "s"
										   ? timer_.seconds()
										   : suffix_ == "min"
												 ? timer_.minutes()
												 : timer_.hours()) << '\n';
		} catch (std::exception& e) {
			std::cout << e.what() << std::endl;
		}
	}
}
