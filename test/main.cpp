
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

int main()
{
	wait();
	auto t0 = std_timer::capture_now_time();
	wait();

	int64_t nt = gTimer.getns(t0);
	if(nt < 0 || nt > one_second)
	{
		std::cerr << "std_timer FAILED\n";
		return -1;
	}

	wait();
	gTimer.init();
	wait();

	nt = gTimer.getns(t0);
	if(nt >= 0 || (-nt) > one_second)
	{
		std::cerr << "std_timer FAILED\n";
		return -1;
	}
	
	wait();
	auto t1 = std_timer::capture_now_time();
	wait();

	nt = gTimer.getns(t1);
	if(nt < 0 || nt > one_second)
	{
		std::cerr << "std_timer FAILED\n";
		return -1;
	}

	nt = gTimer.getns(t1) - gTimer.getns(t0);

	if(nt < 0 || nt > one_second)
	{
		std::cerr << "std_timer FAILED\n";
		return -1;
	}


	std::cout << "std_timer OK\n";
	return 0;
}