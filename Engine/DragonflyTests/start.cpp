#include <stdlib.h>
#include <iostream>
#include "LogManager.h"
#include "UtilityTest.h"
#include "VectorTest.h"
#include "SpriteTest.h"
#include "AudioTest.h"

int main() {
	df::LogManager::getInstance().startUp();
	UtilityTest().run();
	VectorTest().run();
	SpriteTest().run();
	AudioTest().run();
	return 0;
}