
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
	void debug_utils::thread_sleep(int ms_time)
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

	const char* debug_utils::format_nice_delta(char* buffer, const std::size_t buffer_size, const double nanoseconds)
	{
		double ddelta = nanoseconds;
		if (ddelta > 1000000.0)
		{
			//1 ms
			ddelta = ddelta / 1000000.0;

			if (ddelta > 1000)
			{
				// sec
				ddelta = ddelta / 1000.0;
				std::snprintf(buffer, buffer_size, "%lf sec", ddelta);
			}
			else
			{
				std::snprintf(buffer, buffer_size, "%lf ms", ddelta);
			}
		}
		else if (ddelta > 1000.0)
		{
			// ms
			ddelta = ddelta / 1000000.0;
			std::snprintf(buffer, buffer_size, "%lf ms", ddelta);
		}

		return buffer;
	}

	void debug_utils::print_nice_delta(const char* name, const double nanoseconds)
	{
		double ddelta = nanoseconds;

		std::cout << "%![dt]:" << name << "=" << uint64_t(ddelta) << "ns";

		if (ddelta > 1000000.0)
		{
			// ms
			ddelta = ddelta / 1000000.0;

			if (ddelta > 1000)
			{
				// sec
				ddelta = ddelta / 1000.0;
				std::cout << " ~~ " << ddelta << " sec\n";
			}
			else
			{
				std::cout << " ~~ " << ddelta << " ms\n";
			}
		}
		else if (ddelta > 1000.0)
		{
			// ms
			ddelta = ddelta / 1000000.0;
			std::cout << " ~~ " << ddelta << " ms\n";
		}
		else
			std::cout << std::endl;
	}
	void debug_utils::print_nice_delta(const char* name, const std::chrono::high_resolution_clock::time_point& start, const std::chrono::high_resolution_clock::time_point& end)
	{
		std::chrono::duration<double, std::nano> delta = end - start;
		double									 ddelta = delta.count();
		print_nice_delta(name, ddelta);
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
		debug_utils::print_nice_delta(name, start, end);
	}

	debug_avrage_timer_impl::debug_avrage_timer_impl(const char* _name)
		:name(_name)
	{
	}
	void debug_avrage_timer_impl::push_back(int64_t* buffer, std::size_t buffer_size, const int64_t delta_ns)
	{
		std::size_t index = count++ % buffer_size;
		buffer[index] = delta_ns;//add sampls

		if (count % buffer_size == 0)
		{
			//time to display avrage
			count = buffer_size;

			const int64_t* end = buffer + buffer_size;
			const double ratio = 1.0 / double(buffer_size);
			double avrage = 0.0;
			while (buffer != end)
			{
				avrage += double(*buffer++) * ratio;
			}
			debug_utils::print_nice_delta(name, avrage);
		}
	}
	void debug_avrage_timer_impl::print_results(const int64_t* buffer, std::size_t buffer_size)
	{
		std::size_t size = buffer_size;
		if (count < buffer_size)
			size = count;

		const int64_t* end = buffer + size;
		const double ratio = 1.0 / double(size);
		double avrage = 0.0;
		while (buffer != end)
		{
			avrage += double(*buffer++) * ratio;
		}
		debug_utils::print_nice_delta(name, avrage);
	}
	


}