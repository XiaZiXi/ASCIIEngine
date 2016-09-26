#include "JoystickListIterator.h"

df::JoystickListIterator::JoystickListIterator(const JoystickList * p_l)
{
	p_list = p_l;
	first();
}

void df::JoystickListIterator::first()
{
	index = 0;
}

void df::JoystickListIterator::next()
{
	if (index < p_list->count)
		index++;
}

bool df::JoystickListIterator::isDone()
{
	return (index == p_list->count);
}

df::Joystick * df::JoystickListIterator::currentObject()
{
	return p_list->p_joystick[index];;
}