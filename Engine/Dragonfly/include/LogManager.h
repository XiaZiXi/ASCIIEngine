#ifndef __LOG_MANAGER_H__
#define __LOG_MANAGER_H__
#include "Manager.h"

namespace df {
	const int LOGLEVEL_IMPORTANT = 0;
	const int LOGLEVEL_DEFAULT = 1;
	const int LOGLEVEL_LOW = 2;
	//Name of the file we're writing to
	const std::string LOGFILE_NAME = "dragonfly.log";
	class LogManager : public Manager {
	private:
		LogManager();
		LogManager(LogManager const&);
		void operator=(LogManager const&);
		//Do we flush the file after writing to it
		bool do_flush;
		//Pointer to file
		FILE *p_f;
		//Verbosity of our log
		int log_level;
	public:
		~LogManager();
		//Get instance of Log Manager
		static LogManager &getInstance();
		//Return 0 if successful, negative elsewise.
		int startUp();
		//Shuts down log manager and closes file
		void shutDown();
		//Set the flush
		void setFlush(bool flush = true);
		//Write to file w/ verbosity set to default
		int writeLog(const char *fmt, ...);
		//Write to file w/ verbosity
		int writeLog(int logLevel, const char *fmt, ...);
	};
}
#endif