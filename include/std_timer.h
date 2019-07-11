
#pragma once

#include "nstimer_config.h"

#ifdef NSTIMER_DEFAULT_STD
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

	public:
		std_timer() = default;

	public:
		inline void reset()
		{
			m_init_time = std::chrono::high_resolution_clock::now();
		}

		// returns time since reset() or since this->constructor()
		// depends on which was called the last
		inline int64_t cast_ns(const time_capture_t& point) const
		{
			return delta_ns(m_init_time, point);
		}

	protected:
		time_capture_t m_init_time = std_timer::capture_now_time();
	};
}
#endif