#include "WorldManager.h"
#include "LogManager.h"
#include "GraphicsManager.h"
#include "ObjectList.h"
#include "ViewObject.h"
#include "EventCollision.h"
#include "EventOut.h"
#include "EventJoystick.h"
#include "EventStep.h"
#include "EventView.h"
#include "EventKeyboard.h"
#include "EventMouse.h"
#include "utility.h"

df::WorldManager::WorldManager(){
	setType("WorldManager");
}

bool df::WorldManager::isValid(std::string event_type)
{
	if (event_type == OUT_EVENT)
		return true;
	else if (event_type == COLLISION_EVENT)
		return true;
	else if (event_type == STEP_EVENT)
		return false;
	else if (event_type == KEYBOARD_EVENT)
		return false;
	else if (event_type == EVENT_MOUSE)
		return false;
	else if (event_type == JOYSTICK_EVENT)
		return false;
	else if (event_type == VIEW_EVENT)
		return true;
	else 
		return true;
}

df::WorldManager & df::WorldManager::getInstance()
{
	static WorldManager instance;
	return instance;
}

int df::WorldManager::startUp()
{
	LogManager &log_manager = LogManager::getInstance();
	GraphicsManager &gm = GraphicsManager::getInstance();
	boundary = Box(Vector(), (float)gm.getHorizontal(), (float)gm.getVertical());
	view = boundary;
	p_view_following = NULL;
	view_slack = Vector();
	log_manager.writeLog("WorldManager::startUp(): WorldManager has started up successfully!");
	Manager::startUp();
	return 0;
}

void df::WorldManager::shutDown()
{
	ObjectListIterator li(&updates);
	for (li.first(); !li.isDone(); li.next()) {
		//delete li.currentObject();
	}
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
	if (p_o == NULL)
		return -1;
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
	if (p_o == p_view_following) {
		//Get center of view
		float view_center_x = view.getCorner().getX() + view.getHorizontal() / 2;
		float view_center_y = view.getCorner().getY() + view.getVertical() / 2;

		//Compute inner "slack" box edges
		float left = view_center_x - view.getHorizontal() * view_slack.getX() / 2;
		float right = view_center_x + view.getHorizontal() * view_slack.getX() / 2;
		float top = view_center_y - view.getVertical() * view_slack.getY() / 2;
		float bottom = view_center_y + view.getVertical() * view_slack.getY() / 2;

		new_pos = p_o->getPosition();
		if (new_pos.getX() < left)
			view_center_x -= left - new_pos.getX();
		else if (new_pos.getX() > right)
			view_center_x += new_pos.getX() - right;
		if (new_pos.getY() < top)
			view_center_y -= top - new_pos.getY();
		else if (new_pos.getY() > bottom)
			view_center_y += new_pos.getY() - bottom;
		setViewPosition(Vector(view_center_x, view_center_y));
	}
	//send out event if new position is out of bounds of world
	if (new_pos.getX() > getBoundary().getHorizontal() || 
		new_pos.getX() < getBoundary().getCorner().getX() ||
		new_pos.getY() > getBoundary().getVertical() ||
		new_pos.getY() < getBoundary().getCorner().getY()) {
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
			Box b = getWorldBox(p_o, where);
			Box b_temp = getWorldBox(p_temp_o);
			bool a = boxIntersectsBox(b, b_temp);
			if (boxIntersectsBox(b, b_temp) && p_temp_o->isSolid()) 
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

void df::WorldManager::setView(Box new_view)
{
	view = new_view;
}

df::Box df::WorldManager::getView() const
{
	return view;
}

void df::WorldManager::setViewPosition(Vector new_view_pos)
{
	//Make sure horizontal is not out of world boundary
	float x = new_view_pos.getX() - view.getHorizontal() / 2;
	if (x + view.getHorizontal() > boundary.getHorizontal())
		x = boundary.getHorizontal() - view.getHorizontal();
	if (x < 0)
		x = 0;

	//Make sure vertical is not out of world boundary
	float y = new_view_pos.getY() - view.getVertical() / 2;
	if (y + view.getVertical() > boundary.getVertical())
		y = boundary.getVertical() - view.getVertical();
	if (y < 0)
		y = 0;
	Vector new_corner(x, y);
	view.setCorner(new_corner);
}

int df::WorldManager::setViewFollowing(Object * p_new_view_following)
{
	//Set to NULL to turn off following
	if (p_new_view_following == NULL) {
		p_view_following = NULL;
		return 0;
	}

	//Iterate over all objects and make sure p_new_view_following is one
	//of them. Else return error
	ObjectListIterator li(&updates);
	for (li.first(); !li.isDone(); li.next()) {
		if (p_new_view_following == li.currentObject()) {
			p_view_following = p_new_view_following;
			setViewPosition(p_view_following->getPosition());
		}
	}//did not find the thing, return error

	return -1;
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
			Box temp_box = getWorldBox(p_temp_o);
			if(boxIntersectsBox(temp_box, view) ||
				dynamic_cast<ViewObject *>(p_temp_o))
				p_temp_o->draw();
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
