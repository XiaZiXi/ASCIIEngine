#pragma once
#include "Test.h"

class VectorTest : public Test {
private:
	void getSetTest();
	void getMagnitudeTest();
	void normalizeTest();
	void scaleTest();
	void opAddTest();
	void opSubtrTest();
	void opMultTest();
	void opEqTest();
	void opNotEqTest();
public:
	VectorTest();
	void run();
};