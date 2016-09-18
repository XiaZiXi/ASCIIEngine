#pragma once
#include "Joystick.h"
#include "JoystickListIterator.h"

const int MAX_JOYSTICKS = 8;
namespace df {
	class JoystickListIterator;
	class JoystickList {
	private:
		int count;								//Count of objects in list
		Joystick *p_joystick[MAX_JOYSTICKS];	//Array of pointers to objects
	public:
		friend class JoystickListIterator;
		//default constructor
		JoystickList();
		//Insert id in list
		//Return 0 if ok, else -1
		//int insertAt(unsigned int joystick_id);
		Joystick * getJoystickAt(unsigned int id);
		//Remove id from list
		//Return 0 if found, else -1
		//int removeAt(unsigned int joystick_id);
		//Clear list (setting count to 0)
		void clear();
		//Return current count of objs in list
		int getCount() const;
		//Return true if list is empty, else false;
		bool isEmpty();
		//Return true if list if full, else false;
		bool isFull();
	};
}