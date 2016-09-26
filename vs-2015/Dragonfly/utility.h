#pragma once
#include "Vector.h"
#include "Box.h"
#include "Object.h"

//Gets timestamp in hh/mm/ss
char *getTimeStamp();
//Sleep for milliseconds
void sleep(long int ms);
bool positionsIntersect(df::Vector p1, df::Vector p2);
bool boxIntersectsBox(df::Box A, df::Box B);
df::Box getWorldBox(const df::Object *p_o);
df::Box getWorldBox(const df::Object *p_o, df::Vector pos);
df::Vector worldToView(df::Vector world_pos);
df::Vector viewToWorld(df::Vector view_pos);
std::string toString(int i);
bool boxContainsPosition(df::Box box, df::Vector pos);
bool lineIntersectsLine();
bool lineIntersectsBox();
bool circleIntersectsBox();
//Return distance given any two points
float distance(df::Vector p1, df::Vector p2);