#include "LogManager.h"
#include "utility.h"
#include "Box.h"
#include "Vector.h"

#include "UtilityTest.h"

using namespace df;

bool UtilityTest::sleepTest()
{
	return false;
}

bool UtilityTest::positionsIntersectTest()
{
	//Case 1: Positions intersecting
	Vector a(0, 0);
	Vector b(0, 0);
	assertTrue(positionsIntersect(a, b), "positionsIntersect", "Positions intersecting");
	//Case 2: Positions not intersecting
	Vector c(0.5, 0);
	assertFalse(positionsIntersect(a, c), "positionsIntersect", "Positions not intersecting");
	return true;
}

bool UtilityTest::boxIntersectsTest()
{
	//Case 1: Boxes overlapping a/b & b/a
	Box a(Vector(), 5, 5);
	Box b(Vector(2, 2), 5, 5);
	assertTrue(boxIntersectsBox(a, b), "boxIntersectsBox", "Boxes overlap a/b");
	assertTrue(boxIntersectsBox(b, a), "boxIntersectsBox", "Boxes overlap b/a");	
	//Case 2: Boxes touching edges
	Box c(Vector(5, 0), 1, 1);
	assertTrue(boxIntersectsBox(a, c), "boxIntersectsBox", "Boxes touching edges a/c");
	assertTrue(boxIntersectsBox(c, a), "boxIntersectsBox", "Boxes touching edges c/a");
	//Case 3: A box inside another box
	Box d(Vector(1, 1), 1, 1);
	assertTrue(boxIntersectsBox(a, d), "boxIntersectsBox", "Box inside another box a/d");
	assertTrue(boxIntersectsBox(d, a), "boxIntersectsBox", "Box inside another box d/a");
	//Case 4: Boxes not intersecting
	Box e(Vector(10, 10), 3, 3);
	assertFalse(boxIntersectsBox(a, e), "boxIntersectsBox", "Boxes not intersecting a/e");
	assertFalse(boxIntersectsBox(e, a), "boxIntersectsBox", "Boxes not intersecting e/a");
	//Case 5: Same box
	assertTrue(boxIntersectsBox(a, a), "boxIntersectsBox", "Same box");
	return true;
}

bool UtilityTest::getWorldBoxTest()
{
	return false;
}

bool UtilityTest::worldToViewTest()
{
	Vector v(10, 10);
	Vector wtvA = worldToView(v);
	Vector vtwA = viewToWorld(wtvA);
	assertEqual(v.getX(), vtwA.getX(), "worldToView()", "");
	assertEqual(v.getY(), vtwA.getY(), "worldToView()", "");
	return false;
}

bool UtilityTest::viewToWorldTest() {
	Vector v(10, 10);
	Vector vtwA = viewToWorld(v);
	Vector wtvA = worldToView(vtwA);
	assertEqual(v.getX(), wtvA.getX(), "viewToWorld()", "");
	assertEqual(v.getY(), wtvA.getY(), "viewToWorld()", "");
	return true;
}

UtilityTest::UtilityTest()
{
	setup("UtilityTest");
}

void UtilityTest::run()
{
	Test::run();
	sleepTest();
	positionsIntersectTest();
	boxIntersectsTest();
	getWorldBoxTest();
	worldToViewTest();
	viewToWorldTest();
	printResults();
}


