
#include <nstimer.h>
#include <iostream>
#include <thread>
using namespace nstimer;

void wait()
{
	using namespace std::chrono_literals;
	std::this_thread::sleep_for(10ms);
}
int64_t one_second = 1000000000;

std_timer gTimer;
singleton_timer<std_timer> gsTimer;

template <class A, class T>
int test_timer(T * t)
{
	wait();
	auto a = A::capture_now_time(); //<<--- A
	wait();

	auto a0 = t->cast_ns(a);

	wait();
	auto b = A::capture_now_time(); //<<--- B
	wait();
	
	auto a1 = t->cast_ns(a); //A
	auto b1 = t->cast_ns(b); //B
	
	wait();
	t->reset(); //<<--- C 
	wait();

	auto b2 = t->cast_ns(b); //B - C
	auto a2 = t->cast_ns(a); //A - C
	
	
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

	if(! (a0 >= 0 && a0 == a1))
		return 1;

	if(! (b1 > 0 && a1 < b1))
		return 2;

	if(! (a2 < 0 && b2 < 0))
		return 3;

	if(! (a2 < b2))
		return 4;

	if(! (a2 == a3 && a3 == a4))
		return 5;
	
	if(! (b2 == b4 && b3 == b4))
		return 6;

	if(! ( d3 > 0 && d3 == d4 ))
		return 7;

	if(! ( d3 < e4 ))
		return 8;

	if( std::abs(a0) > one_second || std::abs(a1) > one_second || std::abs(a2) > one_second || std::abs(a3) > one_second || std::abs(a4) > one_second)
		return 9;

	if( std::abs(b1) > one_second || std::abs(b2) > one_second || std::abs(b3) > one_second || std::abs(b4) > one_second)
		return 10;
	
	if(std::abs(d3) > one_second || std::abs(d4) > one_second)
		return 11;
	if(std::abs(e4) > one_second)
		return 11;

	return 0;
}
template <class A, class T>
int test_timer_local()
{
	wait();
	auto a = A::capture_now_time(); //<<--- A
	wait();

	//auto a0 = t->cast_ns(a);

	wait();
	T local;
	wait();

	auto a1 = local.cast_ns(a);

	wait();
	auto b = A::capture_now_time(); //<<--- B
	wait();

	auto a2 = local.cast_ns(a);
	auto b2 = local.cast_ns(b);
	

	if(! (a1 < 0) )
		return 101;

	if(! (a1 == a2) )
		return 102;

	if(! (b2 > 0) )
		return 103;

	if(std::abs(a1) > one_second || std::abs(a2) > one_second)
		return 104;
	if(std::abs(b2) > one_second)
		return 105;


	return test_timer<A,T>(&local);
}

template <class A, class T>
bool run_tests(T * global_timer)
{
	int r;

	//before global test
	r = test_timer_local<A,T>();
	if(r != 0)
	{
		std::cerr << "pre test_timer_local<A,T> FAILED:" << r << std::endl;
		return false;
	}

	r = test_timer<A,T>(global_timer);
	if(r != 0)
	{
		std::cerr << "test_timer<A,T> FAILED:" << r << std::endl;
		return false;
	}

	//after global test
	r = test_timer_local<A,T>();
	if(r != 0)
	{
		std::cerr << "post test_timer_local<A,T> FAILED:" << r << std::endl;
		return false;
	}
	return true;
}
std_timer::time_capture_t ref_time = std_timer::capture_now_time();
std_timer::time_capture_t get_time(const singleton_info::storage_t&)
{
	using namespace std::chrono_literals;
	static bool increment_by_100 = false;
	if(increment_by_100)
		ref_time += 101ms;
	else
		ref_time += 1ms;
	increment_by_100 = !increment_by_100;
	return ref_time;
}

int main()
{
	if(run_tests<std_timer,std_timer>(&gTimer) == false)
		return -1;
	
	if(run_tests<singleton_timer<std_timer>,std_timer>(&gTimer) == false)
		return -1;

	singleton_timer<std_timer>::reset(get_time);

	if(run_tests< singleton_timer<std_timer>, singleton_timer<std_timer> >(&gsTimer) == false)
		return -1;

	std::cout << "OK.\n";
	return 0;
}