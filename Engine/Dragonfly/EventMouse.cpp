#include "EventMouse.h"
#include "GraphicsManager.h"

df::EventMouse::EventMouse()
{
	setType(EVENT_MOUSE);
	mouse_action = UNDEFINED_MOUSE_ACTION;
	mouse_button = Mouse::UNDEFINED_MOUSE_BUTTON;
	mouse_xy = Vector();
}

void df::EventMouse::setMouseButton(Mouse::EventMouseButton new_button)
{
	mouse_button = new_button;
}

df::Mouse::EventMouseButton df::EventMouse::getMouseButton() const
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
	Vector pos(new_mouse_xy.getX() / charWidth, new_mouse_xy.getY() / charHeight);
	mouse_xy = pos;
}

df::Vector df::EventMouse::getMousePosition() const
{
	return mouse_xy;
}
