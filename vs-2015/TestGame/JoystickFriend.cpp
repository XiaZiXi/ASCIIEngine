#include "LogManager.h"
#include "JoystickFriend.h"

JoystickFriend::JoystickFriend()
{
}

int JoystickFriend::eventHandler(const df::Event * p_e)
{
	df::LogManager &log_manager = df::LogManager::getInstance();
	if (p_e->getType() == df::JOYSTICK_EVENT) {
		df::EventJoystick *p_j = (df::EventJoystick *)p_e;
		if (p_j->getJoystickAxis() != df::JoystickAxis::UNDEFINED_AXIS) {
			switch (p_j->getJoystickAxis()) {
			case df::JoystickAxis::X:
				log_manager.writeLog("Joystick: JoystickAxis event %u %s %f", p_j->getJoystick(), "X", p_j->getAxisPosition());
				break;
			case df::JoystickAxis::Y:
				log_manager.writeLog("Joystick: JoystickAxis event %u %s %f", p_j->getJoystick(), "Y", p_j->getAxisPosition());
				break;
			}
			log_manager.writeLog("Joystick: JoystickAxis event %u %d %f", p_j->getJoystick(), p_j->getJoystickAxis(), p_j->getAxisPosition());
		}
		else if (p_j->getJoystickButtonAction() != df::JoysickButton::UNDEFINED_BUTTON) {
			log_manager.writeLog("Joystick: JoystickButton event %u %u", p_j->getJoystick(), p_j->getJoystickButton());
		}
	}
	return 0;
}
