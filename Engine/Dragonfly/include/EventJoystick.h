#pragma once
#include "Event.h"
#include "Vector.h"

namespace df {
	const std::string JOYSTICK_EVENT = "df::Joystick";
	namespace JoystickConnection {
		enum EventJoystickConnection {
			DISCONNECT,
			CONNECT
		};
	}
	namespace JoystickAxis {
		enum EventJoystickAxis {
			UNDEFINED_AXIS = -1,
			X = 0,
			Y, Z, R, U, V, PovX, PovY
		};
	}
	
	namespace JoysickButton {
		enum EventJoystickAction {
			UNDEFINED_BUTTON = -1,
			PRESSED,
			RELEASED
		};
	}
	class EventJoystick : public Event {
	private:
		JoystickConnection::EventJoystickConnection connection;
		unsigned int joystick;
		JoystickAxis::EventJoystickAxis axis;
		float axisPos;
		JoysickButton::EventJoystickAction buttonAction;
		unsigned int button;
	public:
		EventJoystick();
		//Set joystick #
		void setJoystick(unsigned int id);
		//Get joystick #
		unsigned int getJoystick() const;
		//Set connection
		void setConnection(JoystickConnection::EventJoystickConnection new_connection);
		//Get connection
		JoystickConnection::EventJoystickConnection getConnection() const;
		//Set joystick button
		void setJoystickButtonAction(JoysickButton::EventJoystickAction new_button);
		//Get joystick button
		JoysickButton::EventJoystickAction getJoystickButtonAction() const;
		void setJoystickButton(unsigned int new_button);
		unsigned int getJoystickButton() const;
		//Sets joystick axis type
		void setJoystickAxis(JoystickAxis::EventJoystickAxis new_axis);
		//Gets joystick axis type
		JoystickAxis::EventJoystickAxis getJoystickAxis() const;
		//Sets x,y of axis
		void setAxisPosition(float new_pos);
		//Gets x,y of axis
		float getAxisPosition() const;
	};
}