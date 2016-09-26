#include "Box.h"

df::Box::Box()
{
	corner = Vector();
	horizontal = 0;
	vertical = 0;
}

df::Box::Box(Vector init_corner, float init_horizontal, float init_vertical)
{
	corner = init_corner;
	horizontal = init_horizontal;
	vertical = init_vertical;
}

void df::Box::setCorner(Vector new_corner)
{
	corner = new_corner;
}

df::Vector df::Box::getCorner() const
{
	return corner;
}

void df::Box::setHorizontal(float new_horiz)
{
	horizontal = new_horiz;
}

float df::Box::getHorizontal() const
{
	return horizontal;
}

void df::Box::setVertical(float new_vert)
{
	vertical = new_vert;
}

float df::Box::getVertical() const
{
	return vertical;
}

bool df::Box::operator==(const Box & other) const
{
	bool same_corner = (corner == other.getCorner());
	return (same_corner && 
		horizontal == other.getHorizontal() && 
		vertical == other.getVertical());
}

bool df::Box::operator!=(const Box & other) const
{
	bool same_corner = (corner == other.getCorner());
	return (!same_corner ||
		horizontal != other.getHorizontal() ||
		vertical != other.getVertical());
}
