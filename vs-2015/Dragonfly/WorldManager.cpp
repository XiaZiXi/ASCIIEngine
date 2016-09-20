#include "WorldManager.h"
#include "LogManager.h"
#include "GraphicsManager.h"
#include "ObjectList.h"
#include "EventCollision.h"
#include "EventOut.h"
#include "utility.h"

df::WorldManager::WorldManager(){
	setType("WorldManager");
	GraphicsManager &gm = GraphicsManager::getInstance();
	boundary = Box(Vector(), (float)gm.getHorizontal(), (float)gm.getVertical());
}

df::WorldManager & df::WorldManager::getInstance()
{
	static WorldManager instance;
	return instance;
}

int df::WorldManager::startUp()
{
	LogManager &log_manager = LogManager::getInstance();
	log_manager.writeLog("WorldManager::startUp(): WorldManager has started up successfully!");
	Manager::startUp();
	return 0;
}

void df::WorldManager::shutDown()
{
	ObjectList ol = (updates);
	ObjectListIterator li(&ol);
	for (li.first(); !li.isDone(); li.next())
		delete li.currentObject();
	Manager::shutDown();
}

int df::WorldManager::insertObject(Object * p_o)
{
	updates.insert(p_o);
	altitudes[p_o->getAltitude()].insert(p_o);
	return 0;
}

int df::WorldManager::removeObject(Object * p_o)
{
	ObjectList ol = (updates);
	ObjectListIterator li(&ol);
	for (li.first(); !li.isDone(); li.next()) {
		if (li.currentObject() == p_o) {
			markForDelete(p_o);
			return 0;
		}
	}
		
	return -1;
}

int df::WorldManager::moveObject(Object *p_o, Vector new_pos)
{
	//check if object we're moving is solid
	if (p_o->isSolid()) {
		ObjectList list = isCollision(p_o, new_pos);
		if (!list.isEmpty()) {
			bool do_move = true;
			ObjectListIterator li(&list);
			while (!li.isDone()) {
				Object *p_temp_o = li.currentObject();
				EventCollision c(p_o, p_temp_o, new_pos);
				p_o->eventHandler(&c);
				p_temp_o->eventHandler(&c);
				if (p_o->getSolidness() == Solidness::HARD && p_temp_o->getSolidness() == Solidness::HARD) {
					do_move = false; //can't move
				}
				li.next();
			}
			if (!do_move)
			{
				return -1;
			} //move not allowed
		} //no collision
	} //object not solid 
	GraphicsManager &graphics_manager = GraphicsManager::getInstance();
	p_o->setPosition(new_pos);
	//send out event if new position is out of bounds
	if (new_pos.getX() > graphics_manager.getHorizontal() || new_pos.getX() < 0 ||
		new_pos.getY() > graphics_manager.getVertical() || new_pos.getY() < 0) {
		EventOut e;
		p_o->eventHandler(&e);
	}
	return 0;
}

df::ObjectList df::WorldManager::isCollision(const Object * p_o, Vector where)
{
	ObjectList collision_list;
	ObjectListIterator li(&updates);
	while (!li.isDone()) {
		Object * p_temp_o = li.currentObject();
		if (p_temp_o != p_o) { //do not check on self
			//if obj is same location and solid
			if (positionsIntersect(p_temp_o->getPosition(), where) && p_temp_o->isSolid()) 
				collision_list.insert(p_temp_o);
		}
		li.next();
	}
	return collision_list;
}

int df::WorldManager::changeAltitude(int old_alt, int new_alt, Object * p_o)
{
	altitudes[old_alt].remove(p_o);
	return altitudes[new_alt].insert(p_o);
}

df::ObjectList df::WorldManager::getAllObjects(bool inactive) const
{
	return (updates);
}

df::ObjectList df::WorldManager::objectsOfType(std::string type) const
{
	ObjectList ol = ObjectList();
	ObjectListIterator li(&updates);
	for (li.first(); !li.isDone(); li.next()) {
		if (li.currentObject()->getType() == type)
			ol.insert(li.currentObject());
	}
	return ol;
}

void df::WorldManager::setBoundary(Box new_boundary)
{
	boundary = new_boundary;
}

df::Box df::WorldManager::getBoundary() const
{
	return boundary;
}

void df::WorldManager::update()
{
	//Update positions based on Object velocities
	ObjectListIterator i(&updates);
	while (!i.isDone()) {
		Vector new_pos = i.currentObject()->predictPosition();
		if (new_pos != i.currentObject()->getPosition()) {
			moveObject(i.currentObject(), new_pos);
		}
		i.next();
	}

	//Delete objects in deletions
	ObjectListIterator li(&deletions);
	li.first();
	while (!li.isDone()) {
		if (li.currentObject() != NULL) {
			delete li.currentObject();
		}
		li.next();
	}
	//clear deletions list
	deletions.clear();
}

void df::WorldManager::draw()
{
	//Iterates thru each layer of objects and draws them
	for (int i = 0; i < MAX_ALTITUDE+1; i++) {
		ObjectList p_ol = (altitudes[i]);
		ObjectListIterator oli(&p_ol);
		for (oli.first(); !oli.isDone(); oli.next()) {
			Object *p_temp_o = oli.currentObject();
			p_temp_o->draw();
			oli.next();
		}
	}
}

int df::WorldManager::markForDelete(Object * p_o)
{
	//Object might be already marked so only add it once
	ObjectListIterator li(&deletions);
	li.first();
	while (!li.isDone()) {
		if (li.currentObject() == p_o)
			return 0;
		li.next();
	}
	//don't update this object anymore
	updates.remove(p_o);
	//don't draw this object anymore
	altitudes[p_o->getAltitude()].remove(p_o);
	//add to deletion list
	return deletions.insert(p_o);
}
