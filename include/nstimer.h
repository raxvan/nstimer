#pragma once

#include "nstimer_config.h"
#include "std_timer.h"
#include "custom_timer.h"

#include <chrono>

namespace nstimer
{

	struct scope_debug_profiler
	{
		const char*									   name;
		std::chrono::high_resolution_clock::time_point start_time;

		scope_debug_profiler(const char* _name);
		~scope_debug_profiler();
	};

}