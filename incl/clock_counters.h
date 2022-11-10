
#pragma once

#ifdef NSTIMER_PLATFORM_WIN32
#	include <intrin.h>
#endif

#if defined(__unix__) || defined(__linux__)
#	include <sched.h>
//#include <linux/getcpu.h>
#endif

#if defined(__QNX__)
// http://www.qnx.com/developers/docs/7.0.0/#com.qnx.doc.neutrino.lib_ref/topic/c/clockcycles.html
#	include <sys/neutrino.h>
#	include <inttypes.h>
#endif

namespace nstimer
{
	// https://github.com/vesperix/FFTW-for-ARMv7/blob/master/kernel/cycle.h

	// arm arch:
	//  https://wiki.ubuntu.com/ARM/Thumb2PortingHowto

#if _MSC_VER >= 1400 && (defined(_M_AMD64) || defined(_M_X64) || defined(_M_IX86))
#	define NSTIMER_CYCLE_TIMER
	//__rdtscp; see https://docs.microsoft.com/en-us/cpp/intrinsics/rdtscp?view=vs-2019
	struct clock_cycle_timer
	{
		using clock_count_t = uint64_t;

		__forceinline static clock_count_t clock_counter()
		{
			return __rdtsc();
		}

		__forceinline static uint32_t core_id()
		{
			uint32_t cid;
			__rdtscp(&cid);
			return cid;
		}
		__forceinline static std::pair<clock_count_t, uint32_t> clock_counter_with_id()
		{
			uint32_t cid; // core id
			uint64_t c = __rdtscp(&cid);
			return { c, cid };
		}
	};

#else

	struct clock_cycle_timer
	{
		using clock_count_t = uint64_t;

#	if defined(__QNX__)
#		define NSTIMER_CYCLE_TIMER
		static __inline__ clock_count_t clock_counter()
		{
			return ClockCycles();
		}

#	elif (defined(__GNUC__) || defined(__ICC) || defined(__SUNPRO_C)) && defined(__x86_64__)
#		define NSTIMER_CYCLE_TIMER
		static __inline__ clock_count_t clock_counter()
		{
			// x86/x64 thing
			unsigned int hi, lo;
			__asm__ volatile("rdtsc" : "=a"(lo), "=d"(hi));
			return ((uint64_t)hi << 32) | lo;
		}
#	elif (defined(__GNUC__) || defined(__ICC)) && defined(__i386__)
#		define NSTIMER_CYCLE_TIMER
		static __inline__ clock_count_t clock_counter()
		{
			uint64_t ret;
			__asm__ __volatile__("rdtsc" : "=A"(ret));
			return ret;
		}
/*#elif defined(__GNUC__) && defined(__aarch64__)
		static __inline__ clock_count_t clock_counter()
		{
			unsigned cc = 0;
			asm volatile("msr cntv_ctl_el0,  %0" : : "r" (cc));
			return uint64_t(cc);
		}
*/
#	endif

#	if defined(__unix__) || defined(__linux__)
		__inline__ static uint32_t core_id()
		{
			return (uint32_t)sched_getcpu();
		}
#	endif
	};

#endif

}
