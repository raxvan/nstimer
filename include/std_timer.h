
#pragma once

#include "nstimer_config.h"

#ifdef NSTIMER_DEFAULT_STD_CHRONO_IMPL
#	include <chrono>

namespace nstimer
{
	struct std_timer
	{
	public: // sampler part:
		using time_capture_t = std::chrono::time_point<std::chrono::high_resolution_clock>;
		static inline time_capture_t capture_now_time()
		{
			return std::chrono::high_resolution_clock::now();
		}
		static inline int64_t delta_ns(const time_capture_t& a, const time_capture_t& b)
		{
			auto delta = b - a;
			auto value = std::chrono::duration_cast<std::chrono::nanoseconds>(delta);
			return (int64_t)value.count();
		}
		static inline int64_t sec_to_ns(const int64_t r)
		{
			return (r) * (int64_t)1e9;
		}

	public:
		std_timer() = default;

	public:
		inline void reset()
		{
			m_init_time = std_timer::capture_now_time();
		}

		// returns time since reset() or since this->constructor()
		// depends on which was called the last
		inline int64_t cast_ns(const time_capture_t& point) const
		{
			return delta_ns(m_init_time, point);
		}

		inline time_capture_t get() const
		{
			return m_init_time;
		}
	protected:
		time_capture_t m_init_time = std_timer::capture_now_time();
	};
}
#endif

//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------

#ifdef NSTIMER_DEFAULT_STD_POSIX_IMPL
#include <cstdint>
#include <time.h>

namespace nstimer
{
	struct std_timer
	{
	public: // sampler part:
		using time_capture_t = timespec;
		static inline time_capture_t capture_now_time()
		{
			timespec now_time;
			clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &now_time);
			return now_time;
		}
		static inline int64_t delta_ns(const time_capture_t& a, const time_capture_t& b)
		{
			return (b.tv_sec - a.tv_sec) * (int64_t)1e9 + (b.tv_nsec - a.tv_nsec);
		}
		static inline int64_t sec_to_ns(const int64_t r)
		{
			return (r) * (int64_t)1e9;
		}

	public:
		std_timer() = default;

	public:
		inline void reset()
		{
			m_init_time = std_timer::capture_now_time();
		}

		// returns time since reset() or since this->constructor()
		// depends on which was called the last
		inline int64_t cast_ns(const time_capture_t& point) const
		{
			return delta_ns(m_init_time, point);
		}

		inline time_capture_t get() const
		{
			return m_init_time;
		}
	protected:
		time_capture_t m_init_time = std_timer::capture_now_time();
	};
}
#endif