#include "JoystickList.h"

df::JoystickList::JoystickList()
{
	count = 0;
	for (int i = 0; i < MAX_JOYSTICKS; i++) {
		p_joystick[i] = new Joystick();
	}
}

df::Joystick * df::JoystickList::getJoystickAt(unsigned int id) {
	return p_joystick[id];
}

//int df::JoystickList::insertAt(unsigned int joystick_id)
//{
//	if (count == MAX_JOYSTICKS)
//		return -1;
//	p_joystick[joystick_id] = p_o;
//	count++;
//	return 0;
//}
//
//int df::JoystickList::removeAt(unsigned int joystick_id)
//{
//	for (int i = 0; i < count; i++) {
//		if (p_joystick[i] == p_o) { //if we found it
//			for (int j = i; j < count - 1; j++) //then shift all objects over
//				p_joystick[j] = p_joystick[j + 1];
//			count--;
//			return 0;
//		}
//	}
//	return -1;
//}

void df::JoystickList::clear()
{
	//null out joysticks? or set them to not connected
	JoystickListIterator li(this);
	while (!li.isDone()) {
		li.currentObject()->setConnection(false);
	}
	count = 0;
}

int df::JoystickList::getCount() const
{
	return count;
}

bool df::JoystickList::isEmpty()
{
	return (count == 0);
}

bool df::JoystickList::isFull()
{
	return (count == MAX_JOYSTICKS);
}
