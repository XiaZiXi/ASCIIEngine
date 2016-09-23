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
	for (int i = 0; i < event_count; i++) {
		if (event[i] == p_e->getType()) {
			ObjectListIterator li(&obj_list[i]);
			while (!li.isDone()) {
				li.currentObject()->eventHandler(p_e);
				count++;
				li.next();
			}
		}
	}
	return count;
}

int df::Manager::registerInterest(Object * p_o, std::string event_type)
{
	for (int i = 0; i < event_count; i++) {
		if (event[i] == event_type) {
			obj_list[i].insert(p_o);
			return 0;
		}
	}
	if (event_count >= MAX_EVENTS) {
		//event list is full
		return -1;
	}
	event[event_count] = event_type;
	obj_list[event_count].clear();
	obj_list[event_count++].insert(p_o);
	return 0;
}

int df::Manager::unregisterInterest(Object * p_o, std::string event_type)
{
	int event_idx = -1;
	for (int i = 0; i < event_count; i++) {
		if (event[i] == event_type) {
			obj_list[i].remove(p_o);
			event_idx = i;
		}
	}
	if (event_idx < 0)
		return -1;
	if (obj_list[event_idx].isEmpty()) {
		obj_list[event_idx] = obj_list[event_count - 1];
		event[event_idx] = event[event_count - 1];
		event_count--;
	}
	return 0;
}

bool df::Manager::isStarted() const
{
	return is_started;
}
