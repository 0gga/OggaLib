#pragma once
#include <string>
#include <chrono>

#include "ogga/stopwatch.hpp"

namespace ogga {
	class scopetimer {
	public:
		scopetimer(std::string_view id) noexcept;
		~scopetimer() noexcept;

	private:
		stopwatch timer_;
		std::ostream* os_;
		std::string id_;
	};

	inline scopetimer::scopetimer(std::string_view id) noexcept
	: id_(id) {
		timer_.start();
	}

	inline scopetimer::~scopetimer() noexcept {
		timer_.stop();
		*os_ << id_ << ": \n" <<
				"   " << timer_.milliseconds() <<
				"   " << timer_.microseconds() <<
				"   " << timer_.nanoseconds() <<
				std::endl;
	}
}
