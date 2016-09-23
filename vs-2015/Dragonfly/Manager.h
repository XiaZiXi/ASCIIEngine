#ifndef __MANAGER_H__
#define __MANAGER_H__
#include <stdlib.h>
#include <string>
#include "Event.h"
#include "ObjectList.h"

namespace df {
	//Maximum # of events allowed
	const int MAX_EVENTS = 100; 
	class Manager {
	private:
		std::string type;		//Manager type identifier
		bool is_started;		//True when started successfully

		int event_count;				//Number of events
		std::string event[MAX_EVENTS];	//List of events
		std::map <std::string, int> events;
		ObjectList obj_list[MAX_EVENTS];	//Objects interested in event
	
		//Check if event is handled by this Manager
		//If handled, return true, else false
		//(Base Manager always returns false)
		virtual bool isValid(std::string event_name) const;

	protected:
		//Set type identifier of Manager
		void setType(std::string t);
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