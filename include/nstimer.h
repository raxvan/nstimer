#pragma once

#include "nstimer_config.h"

#include "std_timer.h"
#include "callback_timer.h"

#include <chrono>

namespace nstimer
{

	struct scope_debug_profiler
	{
		const char*									   name;
		std::chrono::high_resolution_clock::time_point start;

		scope_debug_profiler(const char* _name);
		~scope_debug_profiler();

		static void print_nice_time(const char * name, const std::chrono::high_resolution_clock::time_point& start, const std::chrono::high_resolution_clock::time_point& end);
		static void print_nice_time(const char* name, const double nanoseconds);
	};

	extern void thread_sleep(int ms_time);

}