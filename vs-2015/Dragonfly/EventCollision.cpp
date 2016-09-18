#include "EventCollision.h"

df::EventCollision::EventCollision()
{
	setType(COLLISION_EVENT);
	p_obj1 = NULL;
	p_obj2 = NULL;
	pos = Vector();
}

df::EventCollision::EventCollision(Object * p_o1, Object * p_o2, Vector p)
{
	setType(COLLISION_EVENT);
	p_obj1 = p_o1;
	p_obj2 = p_o2;
	pos = p;
}

void df::EventCollision::setObject1(Object * p_o1)
{
	p_obj1 = p_o1;
}

df::Object * df::EventCollision::getObject1() const
{
	return p_obj1;
}

void df::EventCollision::setObject2(Object * p_o1)
{
	p_obj2 = p_o1;
}

df::Object * df::EventCollision::getObject2() const
{
	return p_obj2;
}

void df::EventCollision::setPosition(Vector new_pos)
{
	pos = new_pos;
}

df::Vector df::EventCollision::getPosition() const
{
	return pos;
}
