#pragma once

class Clock {
private:
	//Last time delta is called
	long int previous_time;
public:
	//Sets previous_time to current time
	Clock();

	//Return time elapsed since delta() was last called, -1 if error.
	//Units are milliseconds.
	long int delta();

	//Return time elasped since delta was called, -1 if error.
	//Units are milliseconds.
	long int split() const;
};