
#include <nstimer.h>
#include <iostream>

#ifdef _MSC_VER
	#include <windows.h>
#elif _POSIX_C_SOURCE >= 199309L
	//^ explain yourself !!!
	#include <time.h>   // for nanosleep
#else
	#include <unistd.h> // for usleep
#endif

namespace nstimer
{
	void thread_sleep(int ms_time)
	{
#ifdef WIN32
		Sleep(ms_time);
#elif _POSIX_C_SOURCE >= 199309L
		struct timespec ts;
		ts.tv_sec = ms_time / 1000;
		ts.tv_nsec = (ms_time % 1000) * 1000000;
		nanosleep(&ts, NULL);
#else
		if (ms_time >= 1000)
			sleep(ms_time / 1000);
		usleep((ms_time % 1000) * 1000);
#endif
	}

#ifdef NSTIMER_DEFAULT_STD
	singleton_adapter_std_timer::callback_ptr_t singleton_adapter_std_timer::_callback = nullptr;
#endif

#ifdef NSTIMER_CUSTOM
	callback_timer_storage::storage_t callback_timer_storage::g_storage;
#endif


	scope_debug_profiler::scope_debug_profiler(const char* _name)
		: name(_name)
	{
		start = std::chrono::high_resolution_clock::now();
	}
	scope_debug_profiler::~scope_debug_profiler()
	{
		auto end = std::chrono::high_resolution_clock::now();
		print_nice_time(name, start, end);
	}
	void scope_debug_profiler::print_nice_time(const char* name, const double nanoseconds)
	{
		double ddelta = nanoseconds;
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
	void scope_debug_profiler::print_nice_time(const char * name, const std::chrono::high_resolution_clock::time_point& start, const std::chrono::high_resolution_clock::time_point& end)
	{
		std::chrono::duration<double, std::nano> delta = end - start;
		double									 ddelta = delta.count();
		print_nice_time(name,ddelta);
	}


}