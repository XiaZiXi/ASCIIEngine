#include <Windows.h>
#include <signal.h>
#include "LogManager.h"
#include "GameManager.h"
#include "Clock.h"
#include "utility.h"
#include "LibraryTests.h"

int LogManager_write() {
	return 0;
}
//This function will intentionally segfault the program
int LogManager_flush(bool isFlush) {
	df::LogManager &lm = df::LogManager::getInstance();
	lm.setFlush(isFlush);
	char a[9];
	lm.writeLog("LibraryTests - LogManager_flush(%s): Starting. Initializing char a[9] and iterating thru it 9 times.", (isFlush ? "true" : "false"));
	for (int i = 0; i < 10; i++) {
		lm.writeLog("LibraryTests - LogManager_flush(%s): a[%d] = 'a'", (isFlush ? "true" : "false"), i);
		a[i] = 'a';
	}
	//raise(SIGSEGV);
	return 0;
}
//Replica of GameManager's run(). Ends while loop when i reaches 100
//Returns true if elapsed time is approx equal to 3.3 seconds
//WINDOWS ONLY TEST
int GameManager_run() {
	int FRAME_TIME_DEFAULT = 33;
	df::LogManager &log_manager = df::LogManager::getInstance();
	df::GameManager &game_manager = df::GameManager::getInstance();
	int i = 0;

	LARGE_INTEGER start, end, elapsed;
	LARGE_INTEGER freq;


	log_manager.writeLog("GameManager_run test start. Running %d loops", 100);

	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&start);

	long int loop_time, intended_sleep_time, adjust_time = 0, actual_sleep_time;
	Clock clock;
	while (i < 100) {
		clock.delta();
		i++;
		loop_time = clock.split();
		intended_sleep_time = FRAME_TIME_DEFAULT - loop_time - adjust_time;
		clock.delta();
		if(intended_sleep_time > 0)
			sleep(intended_sleep_time);
		actual_sleep_time = clock.split();
		adjust_time = actual_sleep_time - intended_sleep_time;
	}
	QueryPerformanceCounter(&end);
	elapsed.QuadPart = end.QuadPart - start.QuadPart;

	elapsed.QuadPart *= 1000;
	elapsed.QuadPart /= freq.QuadPart;
	double elapsedInSeconds = (double)elapsed.QuadPart / 1000;
	log_manager.writeLog("GameManager_run: After running %d game loops, elapsed time is %f seconds", 100, elapsedInSeconds);
	return (elapsedInSeconds < 3.8) && (elapsedInSeconds > 3.0);
}