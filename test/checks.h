
#pragma once

#include <nstimer.h>

#ifdef PRJ_PLATFORM_IS_WIN32
#include <windows.h>
#endif
#ifdef PRJ_PLATFORM_IS_LINUX
#include <unistd.h>
#endif

void checking_std_high_resolution_clock()
{
	std::cout << "checking_std_high_resolution_clock:\n";

	using namespace std::chrono_literals;

	auto t0 = std::chrono::high_resolution_clock::now();
	std::this_thread::sleep_for(1ms);
	auto t1 = std::chrono::high_resolution_clock::now();
	std::this_thread::sleep_for(2ms);
	auto t2 = std::chrono::high_resolution_clock::now();
	std::this_thread::sleep_for(5ms);
	auto t3 = std::chrono::high_resolution_clock::now();
	std::this_thread::sleep_for(15ms);
	auto t4 = std::chrono::high_resolution_clock::now();
	std::this_thread::sleep_for(44ms);
	auto t5 = std::chrono::high_resolution_clock::now();
	std::this_thread::sleep_for(110ms);
	auto t6 = std::chrono::high_resolution_clock::now();
	std::this_thread::sleep_for(1000ms);
	auto t7 = std::chrono::high_resolution_clock::now();

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
}

void check_std_timer_impl()
{
	std::cout << "check_std_timer_impl:\n";

	using namespace std::chrono_literals;

	auto t0 = nstimer::std_timer::capture_now_time();
	std::this_thread::sleep_for(1ms);
	auto t1 = nstimer::std_timer::capture_now_time();
	std::this_thread::sleep_for(2ms);
	auto t2 = nstimer::std_timer::capture_now_time();
	std::this_thread::sleep_for(5ms);
	auto t3 = nstimer::std_timer::capture_now_time();
	std::this_thread::sleep_for(15ms);
	auto t4 = nstimer::std_timer::capture_now_time();
	std::this_thread::sleep_for(44ms);
	auto t5 = nstimer::std_timer::capture_now_time();
	std::this_thread::sleep_for(110ms);
	auto t6 = nstimer::std_timer::capture_now_time();
	std::this_thread::sleep_for(1000ms);
	auto t7 = nstimer::std_timer::capture_now_time();

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
}

void check_platform_sleep_impl_impl()
{
	std::cout << "check_platform_sleep_impl_impl:\n";

	using namespace std::chrono_literals;
#ifdef PRJ_PLATFORM_IS_WIN32
	#define PLATFORM_SLEEP Sleep
#endif
#ifdef PRJ_PLATFORM_IS_LINUX
	#define PLATFORM_SLEEP usleep
#endif
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
}