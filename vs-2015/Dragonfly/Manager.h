#ifndef __MANAGER_H__
#define __MANAGER_H__
#include <stdlib.h>
#include <string>
#include "Event.h"

namespace df {
	class Manager {
	private:
		std::string type;		//Manager type identifier
		bool is_started;		//True when started successfully
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
		//Sends event to all Objects. Returns count of events sent
		virtual int onEvent(const Event *p_e);
		//Returns true when startUp is executed successfully. Otherwise false
		bool isStarted() const;
	};
}
#endif