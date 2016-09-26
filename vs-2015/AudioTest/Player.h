#pragma once
#include "Object.h"

class Player : public df::Object {
public:
	int eventHandler(const df::Event *p_e);
};