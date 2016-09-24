#include "Test.h"

void Test::fail(bool actual, bool expected, std::string test, std::string message, std::string assertname)
{
	char * a = actual ? "true" : "false";
	char * e = expected ? "true" : "false";
	LogManager::getInstance().writeLog("Fail %s %s - Actual: %s Expected: %s - %s", test.c_str(), assertname.c_str(), a, e, message.c_str());
	failCount++;
}

Test::Test()
{
	testname = "";
	testCount = 0;
	successCount = 0;
	failCount = 0;
}

void Test::setup(std::string name)
{
	testname = name;
	LogManager::getInstance().writeLog("Setting up tests for %s...", testname.c_str());
}

bool Test::assertOK(int actual, int expected, std::string test, std::string message)
{
	testCount++;
	if (actual != expected) {
		fail(actual, expected, test, message, "OK");
		return false;
	}
	char * a = actual ? "true" : "false";
	char * e = expected ? "true" : "false";
	LogManager::getInstance().writeLog("Pass %s OK - Actual: %s Expected: %s - %s", test.c_str(), a, e, message.c_str());
	successCount++;
	return true;
}

bool Test::assertERROR(int actual, int expected, std::string test, std::string message)
{
	testCount++;
	if (actual != expected) {
		fail(actual, expected, test, message, "ERROR");
		return false;
	}
	char * a = actual ? "true" : "false";
	char * e = expected ? "true" : "false";
	LogManager::getInstance().writeLog("Pass %s ERROR - Actual: %s Expected: %s - %s", test.c_str(), a, e, message.c_str());
	successCount++;
	return true;
}

bool Test::assertEqual(bool actual, bool expected, std::string test, std::string message)
{
	testCount++;
	if (actual != expected) {
		fail(actual, expected, test, message, "EQUAL");
		return false;
	}
	char * a = actual ? "true" : "false";
	char * e = expected ? "true" : "false";
	LogManager::getInstance().writeLog("Pass %s EQUAL - Actual: %s Expected: %s - %s", test.c_str(), a, e, message.c_str());
	successCount++;
	return true;
}

bool Test::assertEqual(int actual, int expected, std::string test, std::string message)
{
	testCount++;
	if (actual != expected) {
		fail(actual, expected, test, message, "EQUAL");
		return false;
	}
	LogManager::getInstance().writeLog("Pass %s EQUAL - Actual: %d Expected: %d - %s", test.c_str(), actual, expected, message.c_str());
	successCount++;
	return true;
}

bool Test::assertEqual(float actual, float expected, std::string test, std::string message)
{
	testCount++;
	if (actual != expected) {
		fail(actual, expected, test, message, "EQUAL");
		return false;
	}
	LogManager::getInstance().writeLog("Pass %s EQUAL - Actual: %f Expected: %f - %s", test.c_str(), actual, expected, message.c_str());
	successCount++;
	return true;
}

bool Test::assertTrue(bool actual, std::string test, std::string message)
{
	testCount++;
	if (!actual) {
		fail(actual, true, test, message, "TRUE");
		return false;
	}
	char * a = actual ? "true" : "false";
	char * e = "true";
	LogManager::getInstance().writeLog("Pass %s TRUE - Actual: %s Expected: %s - %s", test.c_str(), a, e, message.c_str());
	successCount++;
	return true;
}

bool Test::assertFalse(bool actual, std::string test, std::string message)
{
	testCount++;
	if (actual) {
		fail(actual, false, test, message, "FALSE");
		return false;
	}
	char * a = actual ? "true" : "false";
	char * e = "false";
	LogManager::getInstance().writeLog("Pass %s FALSE - Actual: %s Expected: %s - %s", test.c_str(), a, e, message.c_str());
	successCount++;
	return true;
}

void Test::printResults()
{
	LogManager::getInstance().writeLog("%s COMPLETE. Ran %d tests. %d pass, %d fail.", testname.c_str(), testCount, successCount, failCount);
}

void Test::run()
{
	LogManager::getInstance().writeLog("Running %s", testname.c_str());
}
