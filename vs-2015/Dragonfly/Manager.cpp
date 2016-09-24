#include "Manager.h"
#include "WorldManager.h"

bool df::Manager::isValid(std::string event_name) const
{
	return false;
}

void df::Manager::setType(std::string t)
{
	type = t;
}

df::Manager::Manager()
{
	//This manager has not started yet.
	is_started = false;
}

df::Manager::~Manager()
{
}

std::string df::Manager::getType() const
{
	return type;
}

int df::Manager::startUp()
{
	is_started = true;
	return 0;
}

void df::Manager::shutDown()
{
}

int df::Manager::onEvent(const Event *p_e) const{
	int count = 0;
	//for (int i = 0; i < event_count; i++) {
	//	if (events.find(p_e->getType()) != events.end()) {
	//		//found
	//		ObjectList l = events.at(p_e->getType());
	//		ObjectListIterator li(&l);
	//		while (!li.isDone()) {
	//			li.currentObject()->eventHandler(p_e);
	//			count++;
	//			li.next();
	//		}
	//	}
	//}
	ObjectList l = WorldManager::getInstance().getAllObjects();
	ObjectListIterator ol(&l);
	for (ol.first(); !ol.isDone(); ol.next()) {
		ol.currentObject()->eventHandler(p_e);
		count++;
	}
	return count;
}

int df::Manager::registerInterest(Object * p_o, std::string event_type)
{
	if (events.find(event_type) == events.end()) {
		// not found
		if (event_count >= MAX_EVENTS) {
			//event list is full 
			return -1;
		}
		//Add new ObjectList of that event
		ObjectList *p_objlist = new ObjectList();
		p_objlist->insert(p_o);
		events.insert(std::pair<std::string, ObjectList>(event_type, *(p_objlist)));
		event_count++;
	}
	else {
		// found
		ObjectList l = events[event_type];
		l.insert(p_o);
	}
	return 0;
}

int df::Manager::unregisterInterest(Object * p_o, std::string event_type)
{
	std::map<std::string, ObjectList>::iterator it;
	it = events.find(event_type);
	if (it == events.end()) {
		// not found
		return -1;
	}
	else {
		// found
		//get obj list of event type
		ObjectList l = events[event_type];
		//remove obj from that list
		l.remove(p_o);
		//if this list is now empty, remove it from the map
		if (l.isEmpty()) {
			event_count--;
		}
	}
	return 0;
}

bool df::Manager::isStarted() const
{
	return is_started;
}
