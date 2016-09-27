#ifndef __MANAGER_H__
#define __MANAGER_H__
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include "Event.h"
#include "ObjectList.h"

//Config file to look for
const std::string CONFIG_FILE = "df-config.txt";
//If config file starts w/ '#', skip
const std::string COMMENT_TOKEN = "#";

namespace df {
	//Maximum # of events allowed
	const int MAX_EVENTS = 100; 
	class Manager {
	private:
		std::string type;		//Manager type identifier
		bool is_started;		//True when started successfully

		int event_count;				//Number of events
		std::string events[MAX_EVENTS];
		ObjectList obj_list[MAX_EVENTS];
		//Check if event is handled by this Manager
		//If handled, return true, else false
		//(Base Manager always returns false)
		virtual bool isValid(std::string event_name);
		//Parses config file for engine & game settings
		//Returns 0 if ok, else -1
		virtual int parseConfig();

	protected:
		//Set type identifier of Manager
		void setType(std::string t);

		void discardCR(std::string &str);
		std::string peekLine(std::ifstream * p_file);
		int parseLineInt(std::string *line, const char *tag);
		std::string parseLineStr(std::string *line, const char *tag);
	public:
		Manager();
		virtual ~Manager();
		//Get type identifier of Manager
		std::string getType() const;
		//Returns 0 if startUp executes ok. Otherwise a negative number
		virtual int startUp();
		//Shutdown the manager
		virtual void shutDown();
		//Indicate interest in event
		//Return 0 if ok, else -1
		//(Note: doesn't check to see if object is already registered)
		int registerInterest(Object *p_o, std::string event_type);
		//Indicate no more interest in event
		//Return 0 if ok, else -1
		int unregisterInterest(Object *p_o, std::string event_type);
		//Sends event to all Objects. Returns count of events sent
		int onEvent(const Event *p_e) const;
		//Returns true when startUp is executed successfully. Otherwise false
		bool isStarted() const;
	};
}
#endif