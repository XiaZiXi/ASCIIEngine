#include <stdio.h>
#include <stdarg.h>
#include <limits.h>

#include "LogManager.h"

#include "utility.h"

df::LogManager::LogManager() {
	const char *file_name = LOGFILE_NAME.c_str();
	p_f = std::fopen(file_name, "w+");
	log_level = LOGLEVEL_DEFAULT;
}

df::LogManager::~LogManager()
{
	//Close the file on destruct
	fclose(p_f);
}

df::LogManager &df::LogManager::getInstance()
{
	static LogManager instance;
	return instance;
}

int df::LogManager::startUp()
{
	int lm_success = Manager::startUp();
	writeLog("LogManager::startUp(): Successfully started up.");
	return lm_success;
}

void df::LogManager::shutDown()
{
	writeLog("LogManager::shutDown(): LogManager is shutting down.");
	//delete this;
}

void df::LogManager::setFlush(bool flush)
{
	writeLog(LOGLEVEL_LOW, "LogManager::setFlush(): Setting flush to %s.", flush ? "true" : "false");
	do_flush = flush;
}

int df::LogManager::writeLog(const char *fmt, ...) {
	size_t len;
	char* s;
	va_list args;
	va_start(args, fmt);
	//get length of what this string would be if we formatted with args
	len = (size_t)vsnprintf(NULL, 0, fmt, args);
	//allocate our string to be that size
	s = (char*)malloc(len+1);
	//make the string with the appropriate length
	vsnprintf(s, len+1, fmt, args);
	va_end(args);
	//give public writeLog this string w/ no args
	return writeLog(LOGLEVEL_DEFAULT, s);
}

int df::LogManager::writeLog(int logLevel, const char *fmt, ...) {
	if (p_f == NULL) {
		//If we can't find the file, then throw a tantrum here
		perror("Error opening file 'dragonfly.log'");
		return 1;
	}
	//If log verbosity is less than the set level, 
	if (logLevel < log_level)
		return 0;
	fprintf(p_f, getTimeStamp());
	va_list args;
	va_start(args, fmt);
	vfprintf(p_f, fmt, args);
	va_end(args);
	fprintf(p_f, "\n");
	if (do_flush)
		fflush(p_f);
	return 0;
}