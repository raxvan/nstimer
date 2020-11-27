
#include <nstimer.h>
#include <clock_counters.h>
#include <iostream>
#include <thread>
#include "checks.h"

void wait()
{
	using namespace std::chrono_literals;
	std::this_thread::sleep_for(10ms);
	std::this_thread::yield();
}

int64_t one_second = 1000000000;

nstimer::std_timer					gTimer;
nstimer::callback_timer<nstimer::std_timer> 	gsTimer;
nstimer::std_timer::time_capture_t 	g_global_time = nstimer::std_timer::capture_now_time();

template <class A, class T>
void test_timer(T* t, bool& err)
{
	err = false;
	wait();
	auto a = A::capture_now_time(); //<<--- A
	wait();

	auto a0 = t->cast_ns(a);

	wait();
	auto b = A::capture_now_time(); //<<--- B
	wait();

	auto a1 = t->cast_ns(a); // A
	auto b1 = t->cast_ns(b); // B

	wait();
	t->reset(); //<<--- C
	wait();

	auto b2 = t->cast_ns(b); // B - C
	auto a2 = t->cast_ns(a); // A - C

	wait();
	auto d = A::capture_now_time(); //<<--- D
	wait();

	auto a3 = t->cast_ns(a);
	auto d3 = t->cast_ns(d);
	auto b3 = t->cast_ns(b);

	wait();
	auto e = A::capture_now_time(); //<<--- E
	wait();

	auto d4 = t->cast_ns(d);
	auto e4 = t->cast_ns(e);
	auto a4 = t->cast_ns(a);
	auto b4 = t->cast_ns(b);

	if (!(a0 >= 0 && a0 == a1))
	{
		std::cerr << "Failed test_timer case 1" << std::endl;
		err = true;
	}

	if (!(b1 > 0 && a1 < b1))
	{
		std::cerr << "Failed test_timer case 2" << std::endl;
		err = true;
	}

	if (!(a2 < 0 && b2 < 0))
	{
		std::cerr << "Failed test_timer case 3" << std::endl;
		err = true;
	}

	if (!(a2 < b2))
	{
		std::cerr << "Failed test_timer case 4" << std::endl;
		err = true;
	}

	if (!(a2 == a3 && a3 == a4))
	{
		std::cerr << "Failed test_timer case 5" << std::endl;
		err = true;
	}

	if (!(b2 == b4 && b3 == b4))
	{
		std::cerr << "Failed test_timer case 6" << std::endl;
		err = true;
	}

	if (!(d3 > 0 && d3 == d4))
	{
		std::cerr << "Failed test_timer case 7" << std::endl;
		err = true;
	}

	if (!(d3 < e4))
	{
		std::cerr << "Failed test_timer case 8" << std::endl;
		err = true;
	}

	if (std::abs(a0) > one_second || std::abs(a1) > one_second || std::abs(a2) > one_second || std::abs(a3) > one_second || std::abs(a4) > one_second)
	{
		std::cerr << "Failed test_timer case 9" << std::endl;
		err = true;
	}

	if (std::abs(b1) > one_second || std::abs(b2) > one_second || std::abs(b3) > one_second || std::abs(b4) > one_second)
	{
		std::cerr << "Failed test_timer case 10" << std::endl;
		err = true;
	}

	if (std::abs(d3) > one_second || std::abs(d4) > one_second)
	{
		std::cerr << "Failed test_timer case 11" << std::endl;
		err = true;
	}
	if (std::abs(e4) > one_second)
	{
		std::cerr << "Failed test_timer case 12" << std::endl;
		err = true;
	}
}
template <class A, class T>
void test_timer_local(bool& err)
{
	wait();

	auto start_time = A::capture_now_time(); //<<--- A

	wait();

	T local;

	wait();

	auto delta1 = local.cast_ns(start_time);

	wait();

	auto end_time = A::capture_now_time(); //<<--- B

	wait();

	auto delta2 = local.cast_ns(start_time);
	auto delta3 = local.cast_ns(end_time);

	if (!(delta1 < 0))
	{
		std::cerr << "Failed test_timer_local case 1 [" << delta1 << "]\n";
		err = true;
	}

	if (!(delta1 == delta2))
	{
		std::cerr << "Failed test_timer_local case 2" << std::endl;
		err = true;
	}

	if (!(delta3 > 0))
	{
		std::cerr << "Failed test_timer_local case 2" << std::endl;
		err = true;
	}

	if (std::abs(delta1) > one_second || std::abs(delta2) > one_second)
	{
		std::cerr << "Failed test_timer_local case 3" << std::endl;
		err = true;
	}
	if (std::abs(delta2) > one_second)
	{
		std::cerr << "Failed test_timer_local case 4" << std::endl;
		err = true;
	}

	{
		bool err2;
		test_timer<A, T>(&local, err2);
		err = err || err2;
	}
}

template <class A, class T>
bool run_tests(T* global_timer)
{

	bool err = false;
	// before global test
	test_timer_local<A, T>(err);
	if (err == true)
	{
		std::cerr << "test_timer_local[1] FAILED" << std::endl;
	}

	test_timer<A, T>(global_timer, err);
	if (err == true)
	{
		std::cerr << "test_timer FAILED" << std::endl;
	}

	// after global test
	test_timer_local<A, T>(err);
	if (err == true)
	{
		std::cerr << "test_timer_local[2] FAILED" << std::endl;
	}

	return err;
}



nstimer::std_timer::time_capture_t get_time_callback(const nstimer::callback_timer_storage::storage_t&)
{

	static bool increment_by_100 = false;
#ifdef NSTIMER_DEFAULT_STD_CHRONO_IMPL
	using namespace std::chrono_literals;
	if (increment_by_100)
		g_global_time += 101ms;
	else
		g_global_time += 1ms;
#endif

#ifdef NSTIMER_DEFAULT_STD_POSIX_IMPL
	using namespace std::chrono_literals;
	if (increment_by_100)
		g_global_time.tv_nsec += 1000 * 100;
	else
		g_global_time.tv_nsec += 1000;
#endif
	increment_by_100 = !increment_by_100;
	return g_global_time;
}

int main()
{
	std::cout << "Running test `std_timer`\n";
	auto test1_err = run_tests<nstimer::std_timer, nstimer::std_timer>(&gTimer);

	std::cout << "Running test `std_timer`\n";
	auto test2_err = run_tests<nstimer::callback_timer<nstimer::std_timer>, nstimer::std_timer>(&gTimer);

	std::cout << "Running test `custom_timer<std_timer>/callback`\n";
	nstimer::callback_timer<nstimer::std_timer>::set_global_callback(get_time_callback);

	auto test3_err = run_tests<nstimer::callback_timer<nstimer::std_timer>, nstimer::callback_timer<nstimer::std_timer>>(&gsTimer);


	if (test1_err || test2_err || test3_err)
	{
		std::cout << "FAILED.\n";
		return -1;
	}
	else
	{
		std::cout << "OK.\n";
	}

	{
		checking_std_high_resolution_clock();
		check_std_timer_impl();
		check_platform_sleep_impl_impl();
	}

	return 0;
}