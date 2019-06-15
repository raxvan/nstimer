
#pragma once

#include "nstimer_config.h"

#ifdef NSTIMER_DEFAULT_STD
#include <chrono>

namespace nstimer
{
	struct std_timer
	{
	public: //sampler part:
		using time_capture_t = std::chrono::time_point<std::chrono::high_resolution_clock>;
		static inline time_capture_t 		capture_now_time()
		{
			return std::chrono::high_resolution_clock::now();
		}

	public:
		std_timer() = default;
	public:

		inline void 		init()
		{
			m_init_time = std::chrono::high_resolution_clock::now();
		}

		//returns time since init() or since this->constructor()
		//depends on which was called the last
		inline int64_t		getns(const time_capture_t & point) const //since 1970
		{
			auto delta = point - m_init_time;
			auto value = std::chrono::duration_cast<std::chrono::nanoseconds>(delta);
			return (int64_t)value.count();
		}
		
	protected:
		time_capture_t 	m_init_time = std_timer::capture_now_time();
	};
}
#endif