#pragma once

#include "nstimer_config.h"

#include "std_timer.h"
#include "callback_timer.h"

#include <chrono>

namespace nstimer
{
	struct debug_utils
	{
		static void thread_sleep(int ms_time);
		static void print_nice_delta(const char* name, const std::chrono::high_resolution_clock::time_point& start, const std::chrono::high_resolution_clock::time_point& end);
		static void print_nice_delta(const char* name, const double nanoseconds);
		static const char* format_nice_delta(char* buffer, const std::size_t buffer_size, const double nanoseconds);
	};

	//--------------------------------------------------------------------------------------------------------------------------------

	struct scope_debug_profiler
	{
		const char*									   name;
		std::chrono::high_resolution_clock::time_point start;

		scope_debug_profiler(const char* _name);
		~scope_debug_profiler();
	};


	//--------------------------------------------------------------------------------------------------------------------------------

	template<class C>
	struct scope_delta_accumulator
	{
		std::chrono::high_resolution_clock::time_point start;
		C& container;

		inline scope_delta_accumulator(C& _container)
			:container(_container)
		{
			start = std::chrono::high_resolution_clock::now();
		}
		inline ~scope_delta_accumulator()
		{
			auto end = std::chrono::high_resolution_clock::now();
			container.push_back((int64_t)std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());
		}
	};

	//--------------------------------------------------------------------------------------------------------------------------------	

	struct debug_avrage_timer_impl
	{
	protected:
		const char* name;
		std::size_t count = 0;

		debug_avrage_timer_impl(const char* name);

		void push_back(int64_t* buffer, std::size_t buffer_size, const int64_t delta_ns);
		void print_results(const int64_t* buffer, std::size_t buffer_size);
	};

	template <std::size_t N>
	struct debug_avrage_delta : public debug_avrage_timer_impl
	{
	public:
		using scope_t = scope_delta_accumulator< debug_avrage_delta<N> >;
	protected:
		int64_t		samples[N];
	public:
		inline debug_avrage_delta(const char* name)
			:debug_avrage_timer_impl(name)
		{
		}
		inline ~debug_avrage_delta()
		{
			debug_avrage_timer_impl::print_results(&samples[0], N);
		}

		inline void push_back(int64_t delta_ns)
		{
			debug_avrage_timer_impl::push_back(&samples[0], N, delta_ns);
		}
		inline int64_t print_results()
		{
			return debug_avrage_timer_impl::print_results(&samples[0], N, count);
		}
	};

	//--------------------------------------------------------------------------------------------------------------------------------


}