#include <stdlib.h>
#include "VectorTest.h"

void VectorTest::getSetTest()
{
	Vector v;
	assertEqual(v.getX(), (float)0, "getX()", "Vector(0, 0) has x of 0");
	assertEqual(v.getY(), (float)0, "getY()", "Vector(0, 0) has y of 0");
	v.setX(5);
	assertEqual(v.getX(), (float)5, "getX()", "Vector(5, 0) has x of 5");
	v.setY(10);
	assertEqual(v.getY(), (float)10, "getY()", "Vector(5, 10) has y of 10");
	v.setXY(8, 19);
	assertEqual(v.getX(), (float)8, "getX()", "Vector(8, 19) has x of 8");
	assertEqual(v.getY(), (float)19, "getY()", "Vector(8, 19) has y of 19");
}

void VectorTest::getMagnitudeTest()
{
	//Case 1: No magnitude
	Vector v;
	assertEqual(v.getMagnitude(), (float)0, "getMagnitude()", "No magnitude on Vector(0,0)");
	//Case 2: Positive/Positive vector
	Vector a(2, 1);
	assertEqual(a.getMagnitude(), std::sqrtf(5), "getMagnitude()", "Magnitude of 2, 1 == sqrt5");
	//Case 3: Negative/Negative vector
	Vector b(-1, -1);
	assertEqual(b.getMagnitude(), std::sqrtf(2), "getMagnitude()", "Magnitude of -1, -1 == sqrt2");
	//Case 4: Positive/Negative vector
	Vector c(1, -1);
	assertEqual(c.getMagnitude(), std::sqrtf(2), "getMagnitude()", "Magnitude of 1, -1 == sqrt2");
	//Case 5: Negative/Positive vector
	Vector d(-1, 1);
	assertEqual(d.getMagnitude(), std::sqrtf(2), "getMagnitude()", "Magnitude of -1, 1 == sqrt2");
}

void VectorTest::normalizeTest()
{
	Vector v;
	//Case 1: 0,0
	Vector vn = v;
	vn.normalize();
	bool vx = v.getX() == vn.getX();
	bool vy = v.getY() == vn.getY();
	assertTrue(vx&&vy, "normalize()", "Normalize vector 0,0 == 0,0");
	//Case 2: Negative values
	//Case 3: Positive values
}

void VectorTest::scaleTest()
{
	//Case 1: 0,0
	//Case 2: Negative scale
	//Case 3: Positive scale
}

void VectorTest::opAddTest()
{
	
}

void VectorTest::opSubtrTest()
{
}

void VectorTest::opMultTest()
{
}

void VectorTest::opEqTest()
{
}

void VectorTest::opNotEqTest()
{
}

VectorTest::VectorTest()
{
}

void VectorTest::run()
{
	Test::run();
	getSetTest();
	getMagnitudeTest();
	normalizeTest();
	scaleTest();
	opAddTest();
	opSubtrTest();
	opMultTest();
	opEqTest();
	opNotEqTest();
	printResults();
}
