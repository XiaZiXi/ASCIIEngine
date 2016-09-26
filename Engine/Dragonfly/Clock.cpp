#include <stdlib.h>
#if defined(_WIN32) || defined(_WIN64)
#include <Windows.h>
#elif LINUX
#include <time.h>
#endif

//Compile w/ -lrt
#include <time.h>
#include "Clock.h"

Clock::Clock()
{
#if defined(_WIN32) || defined(_WIN64)
	SYSTEMTIME st;
	GetSystemTime(&st);
	long int msec = (st.wMinute * 60 * 1000)
		+ (st.wSecond * 1000)
		+ (st.wMilliseconds);
	previous_time = msec;
#elif LINUX
	struct timespec ts;
	clock_gettime(CLOCK_REALTIME, &ts);
	long int msec = ts.tv_sec * 1000 + ts.tv_nsec / 1000000;
	previous_time = msec;
#endif
}

long int Clock::delta()
{
	long int elapsed_time;
	long int before_msec, after_msec;
#if defined(_WIN32) || defined(_WIN64)
	SYSTEMTIME st;
	GetSystemTime(&st);
	before_msec = previous_time;
	after_msec = (st.wMinute * 60 * 1000)
		+ (st.wSecond * 1000)
		+ (st.wMilliseconds);
	elapsed_time = after_msec - before_msec;
#elif LINUX
	struct timespec ts;
	clock_gettime(CLOCK_REALTIME, &ts);
	before_msec = previous_time;
	after_msec = after_ts.tv_sec * 1000 + after_ts.tv_nsec / 1000000;
	elapsed_time = after_msec - before_msec;
#endif
	//Set prev time to the after time for the next call
	previous_time = after_msec;
	return elapsed_time;
}

long int Clock::split() const
{
	long int elapsed_time;
	long int before_msec, after_msec;
#if defined(_WIN32) || defined(_WIN64)
	SYSTEMTIME st;
	GetSystemTime(&st);
	before_msec = previous_time;
	after_msec = (st.wMinute * 60 * 1000)
		+ (st.wSecond * 1000)
		+ (st.wMilliseconds);
	elapsed_time = after_msec - before_msec;
#elif LINUX
	struct timespec ts;
	clock_gettime(CLOCK_REALTIME, &ts);
	before_msec = previous_time;
	after_msec = after_ts.tv_sec * 1000 + after_ts.tv_nsec / 1000000;
	elapsed_time = after_msec - before_msec;
#endif
	//dont set previous_time here
	return elapsed_time;
}
