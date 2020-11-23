
#include <nstimer.h>


#include <iostream>

namespace nstimer
{
#ifdef NSTIMER_DEFAULT_STD
	singleton_adapter_std_timer::callback_ptr_t singleton_adapter_std_timer::_callback = nullptr;
#endif

#ifdef NSTIMER_CUSTOM
	custom_timer_info::storage_t custom_timer_info::g_storage;
#endif


	scope_debug_profiler::scope_debug_profiler(const char* _name)
		: name(_name)
	{
		start_time = std::chrono::high_resolution_clock::now();
	}
	scope_debug_profiler::~scope_debug_profiler()
	{
		auto									 end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::nano> delta = end - start_time;
		double									 ddelta = delta.count();

		std::cout << "+[" << name << "] " << uint64_t(ddelta) << " ns";

		if (ddelta > 1000000.0)
		{
			// ms
			ddelta = ddelta / 1000000.0;

			if (ddelta > 1000)
			{
				// sec
				ddelta = ddelta / 1000.0;
				std::cout << " -> " << ddelta << " sec";
			}
			else
			{
				std::cout << " -> " << ddelta << " ms";
			}
		}

		std::cout << std::endl;
	}


}