#pragma once
#include "Test.h"

class SpriteTest : public Test {
private:
	void loadSpriteTest();
	void unloadSpriteTest();
	void getSpriteTest();
public:
	SpriteTest();
	void run();
};