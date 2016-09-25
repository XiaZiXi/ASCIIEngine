#pragma once
#include "LogManager.h"
using namespace df;
class Test {
private:
	std::string testname;
	void fail(bool actual, bool expected, std::string test, std::string message, std::string assertname);
	int testCount;
	int successCount;
	int failCount;
public:
	Test();
	virtual void setup(std::string name);
	bool assertOK(int actual, std::string test, std::string message);
	bool assertERROR(int actual, std::string test, std::string message);
	bool assertEqual(bool actual, bool expected, std::string test, std::string message);
	bool assertEqual(int actual, int expected, std::string test, std::string message);
	bool assertEqual(float actual, float expected, std::string test, std::string message);
	bool assertTrue(bool actual, std::string test, std::string message);
	bool assertFalse(bool actual, std::string test, std::string message);
	void printResults();
	virtual void run();
};