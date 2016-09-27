#pragma once
#include "Test.h"
class UtilityTest : public Test {
private:
	bool sleepTest();
	bool positionsIntersectTest();
	bool boxIntersectsTest();
	bool getWorldBoxTest();
	bool worldToViewTest();
	bool viewToWorldTest();
public:
	UtilityTest();
	void run();
};