#include <SFML/Window/Joystick.hpp>
#include "EventJoystick.h"

df::EventJoystick::EventJoystick()
{
	setType(JOYSTICK_EVENT);
	connection = JoystickConnection::DISCONNECT;
	joystick = 100;		//undefined
	axis = JoystickAxis::UNDEFINED_AXIS;
	buttonAction = JoysickButton::UNDEFINED_BUTTON;
	button = 100; //undefined
	axisPos = 0;
}

void df::EventJoystick::setConnection(JoystickConnection::EventJoystickConnection new_connection)
{
	connection = new_connection;
}

df::JoystickConnection::EventJoystickConnection df::EventJoystick::getConnection() const
{
	return connection;
}

void df::EventJoystick::setJoystick(unsigned int id)
{
	joystick = id;
}

unsigned int df::EventJoystick::getJoystick() const 
{
	return joystick;
}


df::JoysickButton::EventJoystickAction df::EventJoystick::getJoystickButtonAction() const
{
	return buttonAction;
}

void df::EventJoystick::setJoystickButtonAction(JoysickButton::EventJoystickAction new_button)
{
	buttonAction = new_button;
}

void df::EventJoystick::setJoystickButton(unsigned int new_button)
{
	button = new_button;
}

unsigned int df::EventJoystick::getJoystickButton() const
{
	return button;
}

void df::EventJoystick::setJoystickAxis(JoystickAxis::EventJoystickAxis new_axis) {
	axis = new_axis;
}

df::JoystickAxis::EventJoystickAxis df::EventJoystick::getJoystickAxis() const {
	return axis;
}

void df::EventJoystick::setAxisPosition(float new_pos)
{
	axisPos = new_pos;
}

float df::EventJoystick::getAxisPosition() const
{
	return axisPos;
}
