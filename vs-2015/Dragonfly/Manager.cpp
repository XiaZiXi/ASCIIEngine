#include "Manager.h"
#include "WorldManager.h"

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

int df::Manager::onEvent(const Event *p_e) {
	int count = 0;
	df::WorldManager &world_manager = df::WorldManager::getInstance();
	ObjectList world_objects = world_manager.getAllObjects();
	ObjectListIterator li(&world_objects);
	li.first();
	while (!li.isDone()) {
		li.currentObject()->eventHandler(p_e);
		li.next();
		count++;
	}
	return count;
}

bool df::Manager::isStarted() const
{
	return is_started;
}
