#pragma once
#include "EventJoystick.h"

//Wrapper class for sfml joystick
namespace df {
	class Joystick {
	private:
		unsigned int id;
		//is joystick connected
		bool connected;
		//how many buttons does this joystick have
		unsigned int buttons;
	public:
		Joystick();
		float getAxisPosition(JoystickAxis::EventJoystickAxis axis) const;
		unsigned int getButtonCount() const;
		bool hasAxis(JoystickAxis::EventJoystickAxis axis);
		bool isButtonPressed(unsigned int button);
		void setConnection(bool new_connection);
		bool isConnected(unsigned int id) const;
		int eventHandler(Event *p_e);
	};
}