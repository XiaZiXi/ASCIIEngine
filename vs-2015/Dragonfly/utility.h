#pragma once
#include "Vector.h"
//Gets timestamp in hh/mm/ss
char *getTimeStamp();
//Sleep for milliseconds
void sleep(long int ms);
bool positionsIntersect(df::Vector p1, df::Vector p2);