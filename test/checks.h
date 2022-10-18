
#pragma once

#include <nstimer.h>

#ifdef NSTIMER_PLATFORM_WIN32
#include <windows.h>
#endif
#ifdef NSTIMER_PLATFORM_LINUX
#include <unistd.h>
#endif

#define STD_THREAD_SLEEP(MS) std::this_thread::sleep_for(std::chrono::milliseconds(MS));

void checking_std_high_resolution_clock()
{
#ifdef NSTIMER_DEFAULT_STD_CHRONO_IMPL
	std::cout << "checking_std_high_resolution_clock:\n";

	auto t0 = std::chrono::high_resolution_clock::now();
	STD_THREAD_SLEEP(1);
	auto t1 = std::chrono::high_resolution_clock::now();
	STD_THREAD_SLEEP(2);
	auto t2 = std::chrono::high_resolution_clock::now();
	STD_THREAD_SLEEP(5);
	auto t3 = std::chrono::high_resolution_clock::now();
	STD_THREAD_SLEEP(15);
	auto t4 = std::chrono::high_resolution_clock::now();
	STD_THREAD_SLEEP(44);
	auto t5 = std::chrono::high_resolution_clock::now();
	STD_THREAD_SLEEP(110);
	auto t6 = std::chrono::high_resolution_clock::now();
	STD_THREAD_SLEEP(1000);
	auto t7 = std::chrono::high_resolution_clock::now();
	STD_THREAD_SLEEP(1500);
	auto t8 = std::chrono::high_resolution_clock::now();

	auto print_results = [](double waitms, const auto& start, const auto& end)
	{
		auto	delta = end - start;
		auto	deltans = std::chrono::duration_cast<std::chrono::nanoseconds>(delta);
		int64_t iv = (int64_t)deltans.count();
		std::cout << waitms << " ms sleep == " << iv << " ns => [1 ms ~ " << int64_t(double(iv) / waitms) << " ns]\n";
		std::cout << "raw duration == " << deltans.count() << std::endl;
	};

	print_results(1.0, t0, t1);
	print_results(2.0, t1, t2);
	print_results(5.0, t2, t3);
	print_results(15.0, t3, t4);
	print_results(44.0, t4, t5);
	print_results(110.0, t5, t6);
	print_results(1000.0, t6, t7);
	print_results(1500.0, t7, t8);
#endif
}


void check_std_timer_impl()
{
	std::cout << "check_std_timer_impl:\n";

	auto t0 = nstimer::std_timer::capture_now_time();
	STD_THREAD_SLEEP(1);
	auto t1 = nstimer::std_timer::capture_now_time();
	STD_THREAD_SLEEP(2);
	auto t2 = nstimer::std_timer::capture_now_time();
	STD_THREAD_SLEEP(5);
	auto t3 = nstimer::std_timer::capture_now_time();
	STD_THREAD_SLEEP(15);
	auto t4 = nstimer::std_timer::capture_now_time();
	STD_THREAD_SLEEP(44);
	auto t5 = nstimer::std_timer::capture_now_time();
	STD_THREAD_SLEEP(110);
	auto t6 = nstimer::std_timer::capture_now_time();
	STD_THREAD_SLEEP(1000);
	auto t7 = nstimer::std_timer::capture_now_time();
	STD_THREAD_SLEEP(1500);
	auto t8 = nstimer::std_timer::capture_now_time();

	auto print_results = [](double waitms, const auto& start, const auto& end)
	{
		int64_t iv = nstimer::std_timer::delta_ns(start, end);
		std::cout << waitms << " ms sleep == " << iv << " ns => [1 ms ~ " << int64_t(double(iv) / waitms) << " ns]\n";
	};

	print_results(1.0, t0, t1);
	print_results(2.0, t1, t2);
	print_results(5.0, t2, t3);
	print_results(15.0, t3, t4);
	print_results(44.0, t4, t5);
	print_results(110.0, t5, t6);
	print_results(1000.0, t6, t7);
	print_results(1500.0, t7, t8);
}

void check_native_thread_sleep()
{
	std::cout << "check_native_thread_sleep:\n";

#ifdef NSTIMER_PLATFORM_WIN32
	#define PLATFORM_SLEEP Sleep
#endif
#ifdef NSTIMER_PLATFORM_LINUX
	//usleep microseconds
	#define PLATFORM_SLEEP(MS) usleep(MS * 1000)
#endif
	using timepoint_t = nstimer::std_timer::time_capture_t;

	auto t0 = nstimer::std_timer::capture_now_time();
	PLATFORM_SLEEP(1);
	auto t1 = nstimer::std_timer::capture_now_time();
	PLATFORM_SLEEP(2);
	auto t2 = nstimer::std_timer::capture_now_time();
	PLATFORM_SLEEP(5);
	auto t3 = nstimer::std_timer::capture_now_time();
	PLATFORM_SLEEP(15);
	auto t4 = nstimer::std_timer::capture_now_time();
	PLATFORM_SLEEP(44);
	auto t5 = nstimer::std_timer::capture_now_time();
	PLATFORM_SLEEP(110);
	auto t6 = nstimer::std_timer::capture_now_time();
	PLATFORM_SLEEP(1000);
	auto t7 = nstimer::std_timer::capture_now_time();
	PLATFORM_SLEEP(1500);
	auto t8 = nstimer::std_timer::capture_now_time();

	auto print_results = [](double waitms, const timepoint_t& start, const timepoint_t& end)
	{
		int64_t iv = nstimer::std_timer::delta_ns(start, end);
		std::cout << waitms << " ms sleep == " << iv << " ns => [1 ms ~ " << int64_t(double(iv) / waitms) << " ns]\n";
	};

	print_results(1.0, t0, t1);
	print_results(2.0, t1, t2);
	print_results(5.0, t2, t3);
	print_results(15.0, t3, t4);
	print_results(44.0, t4, t5);
	print_results(110.0, t5, t6);
	print_results(1000.0, t6, t7);
	print_results(1500.0, t7, t8);
}
