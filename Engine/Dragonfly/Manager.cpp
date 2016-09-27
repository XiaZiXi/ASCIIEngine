#include <iostream>
#include <fstream>
#include "Manager.h"
#include "LogManager.h"
#include "WorldManager.h"

bool df::Manager::isValid(std::string event_name)
{
	return false;
}

int df::Manager::parseConfig()
{
	return 0;
}

void df::Manager::discardCR(std::string & str)
{
	if (str.size() > 0 && str[str.size() - 1] == '\r')
		str.erase(str.size() - 1);
}

//Peek next line
std::string df::Manager::peekLine(std::ifstream * p_file)
{
	std::string s;
	std::streampos sp = p_file->tellg();
	getline(*(p_file), s);
	p_file->seekg(sp);
	return s;
}

int df::Manager::parseLineInt(std::string * line, const char * tag)
{
	int s = strlen(tag);
	if (strlen(tag) > (*line).length())
		return -1;
	if ((*line).compare(0, strlen(tag), tag)) {
		return -1;
	}
	int number = atoi((*line).substr(strlen(tag) + 1).c_str());
	if (number == 0) {
		return -1;
	}
	return number;
}

std::string df::Manager::parseLineStr(std::string * line, const char * tag)
{
	int s = strlen(tag);
	if (strlen(tag) > (*line).length())
		return "";
	std::string ret;
	if ((*line).compare(0, strlen(tag), tag))
		return "";
	ret = (*line).substr(strlen(tag) + 1);
	return ret;
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

int df::Manager::onEvent(const Event *p_e) const {
	int count = 0;
	for (int i = 0; i < event_count; i++) {
		if (events[i] == p_e->getType()) {
			ObjectList l = obj_list[i];
			ObjectListIterator li(&l);
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
	if (!isValid(event_type))
		return -1;

	for (int i = 0; i < event_count; i++) {
		if (events[i] == event_type) {
			obj_list[i].insert(p_o);
			return 0;
		}
	}

	if (event_count >= MAX_EVENTS) {
		return -1;
	}
	events[event_count] = event_type;
	obj_list[event_count].clear();
	obj_list[event_count].insert(p_o);
	event_count++;
	return 0;
}

int df::Manager::unregisterInterest(Object * p_o, std::string event_type)
{
	if (!isValid(event_type))
		return -1;
	int idx = -1;
	for (int i = 0; i < event_count; i++) {
		if (events[i] == event_type) {
			obj_list[i].remove(p_o);
			idx = i;
		}
	}
	if (idx == -1)
		return -1;
	//Is list now empty?
	if (obj_list[idx].isEmpty()) {
		for (int i = 0; i < event_count - 1; i++)
			obj_list[i] = obj_list[i + 1];
		for (int j = 0; j < event_count - 1; j++)
			events[j] = events[j + 1];
		events[event_count] = "";
		obj_list[event_count].clear();
		event_count--;
	}

	return 0;
}

bool df::Manager::isStarted() const
{
	return is_started;
}
