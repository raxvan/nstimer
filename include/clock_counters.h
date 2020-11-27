
#pragma once

#ifdef PRJ_PLATFORM_IS_WIN32
#	include <intrin.h>
#endif

namespace nstimer
{

#ifdef PRJ_PLATFORM_IS_WIN32
	//__rdtscp; see https://docs.microsoft.com/en-us/cpp/intrinsics/rdtscp?view=vs-2019
	struct clock_cycle_timer
	{
		struct time_capture_t
		{
			uint64_t clock_index;
			uint32_t core_id; // TSC_AUX[31:0]
		};

		inline static time_capture_t capture_now_time()
		{
			time_capture_t result;
			result.clock_index = __rdtscp(&result.core_id);
			return result;
		}

		inline static uint32_t get_core_id()
		{
			uint32_t cid;
			__rdtscp(&cid);
			return cid;
		}
	};
#endif

}