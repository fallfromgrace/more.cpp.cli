#pragma once

#pragma managed(push, off)
#include <cassert>
#include <chrono>
#pragma managed(pop)

namespace interop
{
	/// <summary>
	/// Converts the specified std::tm to a System::DateTime.
	/// </summary>
	System::DateTime to_DateTime(const std::tm& time, System::Int32 milliseconds)
	{
		return System::DateTime(
			time.tm_year + 1900,
			time.tm_mon + 1,
			time.tm_mday,
			time.tm_hour,
			time.tm_min,
			time.tm_sec,
			milliseconds);
	}

	/// <summary>
	/// Converts the specified std::tm to a System::DateTime.
	/// </summary>
	System::DateTime to_DateTime(const std::tm& time)
	{
		return to_DateTime(time, 0);
	}

	/// <summary>
	/// Converts the specified std::chrono::system_clock::time_point to a System::DateTime.
	/// </summary>
	System::DateTime to_DateTime(const std::chrono::system_clock::time_point& time)
	{
		std::tm tm;
		time_t tt = std::chrono::system_clock::to_time_t(time);
		errno_t err = localtime_s(&tm, &tt);
		assert(err == 0);
		int64_t milliseconds = (time - std::chrono::system_clock::from_time_t(tt)).count();
		return to_DateTime(tm, milliseconds);
	}
}