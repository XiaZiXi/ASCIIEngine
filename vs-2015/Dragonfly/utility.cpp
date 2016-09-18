#include <stdlib.h>
#include <stdio.h>
#if defined(_WIN32) || defined(_WIN64)
#include <Windows.h>
#elif LINUX

#endif
#include <time.h>
#include "GraphicsManager.h"
#include "Vector.h"
#include "utility.h"

char *getTimeStamp()
{
	static char time_str[30];
	time_t now;
	time(&now);
	struct tm *p_time = localtime(&now);
	sprintf(time_str, "[%02d:%02d:%02d]: ",
		p_time->tm_hour,
		p_time->tm_min,
		p_time->tm_sec
		);
	return time_str;
}
//Sleep for a # of milliseconds
void sleep(long int ms) {
#if defined(_WIN32) || defined(_WIN64)
	Sleep(ms);
#elif LINUX
	struct timespec sleep_time;
	sleep_time.tv_sec = 0;
	sleep_time.tv_nsec = ms * 1000000;
	nanosleep(&sleep_time, NULL);
#endif
}

bool positionsIntersect(df::Vector p1, df::Vector p2) {
	if (abs(p1.getX() - p2.getX()) < 1 && abs(p1.getY() - p2.getY()) < 1)
		return true;
	else
		return false;
}