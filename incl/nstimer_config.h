
#pragma once

#define NSTIMER_DEFAULT_STD

#if defined(_MSC_VER) || defined(__APPLE__)
#	define NSTIMER_DEFAULT_STD_CHRONO_IMPL // use std::chrono
#else
#	define NSTIMER_DEFAULT_STD_POSIX_IMPL // use clock_gettime;
// see https://stackoverflow.com/questions/6749621/how-to-create-a-high-resolution-timer-in-linux-to-measure-program-performance
#endif

#define NSTIMER_CUSTOM

//----------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------
