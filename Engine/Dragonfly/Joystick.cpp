#include <SFML/Window/Joystick.hpp>
#include "Joystick.h"

df::Joystick::Joystick()
{
	id = 100;
	connected = false;
	buttons = 0;
}

float df::Joystick::getAxisPosition(JoystickAxis::EventJoystickAxis axis) const
{
	return sf::Joystick::getAxisPosition(id, (sf::Joystick::Axis) axis);
}

unsigned int df::Joystick::getButtonCount() const
{
	return sf::Joystick::getButtonCount(id);
}

bool df::Joystick::hasAxis(JoystickAxis::EventJoystickAxis axis)
{
	return sf::Joystick::hasAxis(id, (sf::Joystick::Axis)axis);
}

bool df::Joystick::isButtonPressed(unsigned int button)
{
	return sf::Joystick::isButtonPressed(id, button);
}

void df::Joystick::setConnection(bool new_connection)
{
	connected = new_connection;
}

bool df::Joystick::isConnected(unsigned int id) const
{
	return connected;
}

int df::Joystick::eventHandler(Event * p_e)
{
	if (p_e->getType() == JOYSTICK_EVENT) {
		EventJoystick * p_j = dynamic_cast<EventJoystick *>(p_e);
		if (p_j->getJoystick() == id) {
			//do stuff
		}
	}
	return 0;
}