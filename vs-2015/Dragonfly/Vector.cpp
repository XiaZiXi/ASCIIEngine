#include <math.h>
#include "Vector.h"

df::Vector::Vector(float init_x, float init_y)
{
	x = init_x;
	y = init_y;
}

df::Vector::Vector()
{
	x = 0.0f;
	y = 0.0f;
}

void df::Vector::setX(float new_x)
{
	x = new_x;
}

float df::Vector::getX() const
{
	return x;
}

void df::Vector::setY(float new_y)
{
	y = new_y;
}

float df::Vector::getY() const
{
	return y;
}

void df::Vector::setXY(float new_x, float new_y)
{
	x = new_x;
	y = new_y;
}

float df::Vector::getMagnitude() const
{
	float mag = (float) sqrt(x*x + y*y);
	return mag;
}

void df::Vector::normalize()
{
	float length = getMagnitude();
	if (length > 0) {
		x /= length;
		y /= length;
	}
}

void df::Vector::scale(float s)
{
	x *= s;
	y *= s;
}

df::Vector df::Vector::operator+(const Vector & other) const
{
	Vector v;
	v.x = x + other.x;
	v.y = y + other.y;
	return v;
}

df::Vector df::Vector::operator-(const Vector & other) const
{
	Vector v;
	v.x = x - other.x;
	v.y = y - other.y;
	return v;
}

df::Vector df::Vector::operator*(const Vector & other) const
{
	Vector v;
	v.x = x * other.x;
	v.y = y * other.y;
	return v;
}

bool df::Vector::operator==(const Vector & other) const
{
	return (x == other.x && y == other.y);
}

bool df::Vector::operator!=(const Vector & other) const
{
	return !(x == other.x && y == other.y);
}
