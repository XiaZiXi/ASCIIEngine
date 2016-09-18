#pragma once
#include "Object.h"
#include "EventJoystick.h"
class JoystickFriend : public df::Object {
public:
	JoystickFriend();
	int eventHandler(const df::Event * p_e);
};