#include "EventMouse.h"
#include "GraphicsManager.h"

df::EventMouse::EventMouse()
{
	mouse_action = UNDEFINED_MOUSE_ACTION;
	mouse_button = UNDEFINED_MOUSE_BUTTON;
	mouse_xy = Vector();
	setType(EVENT_MOUSE);
}

void df::EventMouse::setMouseButton(EventMouseButton new_button)
{
	mouse_button = new_button;
}

df::EventMouseButton df::EventMouse::getMouseButton() const
{
	return mouse_button;
}

void df::EventMouse::setMouseAction(EventMouseAction new_action)
{
	mouse_action = new_action;
}

df::EventMouseAction df::EventMouse::getMouseAction() const
{
	return mouse_action;
}

void df::EventMouse::setMousePosition(Vector new_mouse_xy)
{
	GraphicsManager &graphics_manager = GraphicsManager::getInstance();
	float charWidth = (float)graphics_manager.getHorizontalPixels() /
		(float)graphics_manager.getHorizontal();
	float charHeight = (float)graphics_manager.getVerticalPixels() /
		(float)graphics_manager.getVertical();
	Vector pos(charWidth / new_mouse_xy.getX(), charHeight / new_mouse_xy.getY());
	mouse_xy = pos;
}

df::Vector df::EventMouse::getMousePosition() const
{
	return mouse_xy;
}
