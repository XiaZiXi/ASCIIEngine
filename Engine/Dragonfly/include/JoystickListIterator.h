#pragma once
#include "JoystickList.h"

namespace df {
	class JoystickList;
	class JoystickListIterator {
	private:
		JoystickListIterator();		//Must be given list when created
		const JoystickList *p_list;	//Point to ObjList iterating over
		int index;					//Index of current item
	public:
		JoystickListIterator(const JoystickList *p_l);
		//Set iterator to first item in list
		void first();
		//Iterate to next item in list
		void next();
		//Return true if done iterating, else false
		bool isDone();
		//Return current item
		Joystick *currentObject();
	};
}