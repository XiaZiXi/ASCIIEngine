#pragma once

#include "Object.h"
#include "EventKeyboard.h"
#include "EventMouse.h"
#include "EventJoystick.h"
class Hero : public df::Object {
private:
	int timeToDie;
	void handleKey(df::EventKeyboard *p_k);
	void handleMouse(df::EventMouse *p_m);
	void handleJoystick(df::EventJoystick *p_j);
public:
	Hero();
	~Hero();
	int eventHandler(const df::Event *p_e);
	void draw();
};