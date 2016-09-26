#include <stdlib.h>
#include <stdio.h>
#include <sstream>
#if defined(_WIN32) || defined(_WIN64)
#include <Windows.h>
#elif LINUX
#include <time.h>
#endif
#include "GraphicsManager.h"
#include "WorldManager.h"
#include "Object.h"
#include "Vector.h"
#include "utility.h"

using std::stringstream;

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
	if (p1.getX() == p2.getX() && p1.getY() == p2.getY())
		return true;
	else
		return false;
}

bool boxIntersectsBox(df::Box A, df::Box B)
{
	df::Vector b1 = B.getCorner();
	df::Vector a1 = A.getCorner();
	df::Vector a2(A.getHorizontal(), A.getVertical());
	df::Vector b2(B.getHorizontal(), B.getVertical());
	a2 = a2 + a1;
	b2 = b2 + b1;
	//Test horizontal overlap
	bool x_overlap = (b1.getX() <= a1.getX()) &&
		(a1.getX() <= b2.getX());
	x_overlap = x_overlap ||
		((a1.getX() <= b1.getX()) && 
			(b1.getX() <= a2.getX()));
	//Test vertical overlap
	bool y_overlap = (b1.getY() <= a1.getY()) &&
		(a1.getY() <= b2.getY());
	y_overlap = y_overlap ||
		(a1.getY() <= b1.getY()) &&
			(b1.getY() <= a2.getY());
	return x_overlap && y_overlap;
}

df::Box getWorldBox(const df::Object *p_o) {
	return getWorldBox(p_o, p_o->getPosition());
}

df::Box getWorldBox(const df::Object *p_o, df::Vector pos) {
	df::Box temp_box = p_o->getBox();
	df::Vector corner = temp_box.getCorner();
	corner.setX(corner.getX() + pos.getX());
	corner.setY(corner.getY() + pos.getY());
	temp_box.setCorner(corner);
	return temp_box;
}

df::Vector worldToView(df::Vector world_pos)
{
	df::Vector view_origin = df::WorldManager::getInstance().getView().getCorner();
	float view_x = view_origin.getX();
	float view_y = view_origin.getY();
	df::Vector view_pos(world_pos.getX() - view_x, world_pos.getY() - view_y);
	return view_pos;
}

df::Vector viewToWorld(df::Vector view_pos) {
	df::Vector world_origin = df::WorldManager::getInstance().getBoundary().getCorner();
	float world_x = world_origin.getX();
	float world_y = world_origin.getY();
	df::Vector world_pos(view_pos.getX() + world_x, view_pos.getY() + world_y);
	return world_pos;
}

std::string toString(int i) {
	std::stringstream ss;
	ss << i;
	return ss.str();
}