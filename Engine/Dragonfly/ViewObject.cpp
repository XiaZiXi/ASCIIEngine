#include "LogManager.h"
#include "WorldManager.h"
#include "GraphicsManager.h"

#include "ViewObject.h"
#include "utility.h"
#include "EventView.h"

df::ViewObject::ViewObject()
{
	//Init obj attrs
	setSolidness(SPECTRAL);
	setAltitude(MAX_ALTITUDE);
	setType("ViewObject");

	//Init ViewObject attrs
	setValue(0);
	setDrawValue();
	setBorder(true);
	setLocation(TOP_CENTER);
	setColor(COLOR_DEFAULT);

	registerInterest(VIEW_EVENT);
}

void df::ViewObject::draw()
{
	std::string temp_str;
	if (draw_value)
		temp_str = getViewString() + " " + toString(value);
	else
		temp_str = getViewString();
	//Pad it
	if (border)
		temp_str = " " + temp_str + " ";
	//Draw centered at pos
	Vector pos = viewToWorld(getPosition());
	GraphicsManager::getInstance().drawString(pos, temp_str, CENTER_JUSTIFIED, getColor());
	if (border) {
		//draw box around display
		Vector border_pos_top = Vector(pos.getX(), pos.getY() - 1.0f);
		Vector border_pos_bot = Vector(pos.getX(), pos.getY() + 1.0f);
		std::string width_border;
		int width = temp_str.length();
		int height = 3;
		width_border += '+';
		for (int i = 0; i < width - 2; i++) {
			width_border += '-';
		}
		width_border += '+';
		GraphicsManager::getInstance().drawString(border_pos_top, width_border, CENTER_JUSTIFIED, getColor());
		GraphicsManager::getInstance().drawString(border_pos_bot, width_border, CENTER_JUSTIFIED, getColor());
	}
}

int df::ViewObject::eventHandler(const Event * p_e)
{
	if (p_e->getType() == VIEW_EVENT) {
		const EventView *p_ve = static_cast<const EventView *>(p_e);
		if (p_ve->getTag() == getViewString()) {
			if (p_ve->getDelta())
				setValue(getValue() + p_ve->getValue());
			else
				setValue(p_ve->getValue());
			return 1;
		}
	}
	return 0;
}

void df::ViewObject::setLocation(ViewObjectLocation new_location)
{
	Vector p;
	int y_delta = 0;
	WorldManager &wm = df::WorldManager::getInstance();
	switch (new_location) {
	case TOP_LEFT:
		p.setXY((wm.getView().getHorizontal() * (1.0f / 6.0f)), 1);
		break;
	case TOP_CENTER:
		p.setXY((wm.getView().getHorizontal() * (3.0f / 6.0f)), 1);
		break;
	case TOP_RIGHT:
		p.setXY((wm.getView().getHorizontal() * (5.0f / 6.0f)), 1);
		break;
	case CENTER_LEFT:
		p.setXY((wm.getView().getHorizontal() * (1.0f / 6.0f)), (wm.getView().getVertical() * (1.0f / 2.0f)));
		break;
	case CENTER_CENTER:
		p.setXY((wm.getView().getHorizontal() * (3.0f / 6.0f)), (wm.getView().getVertical() * (1.0f / 2.0f)));
		break;
	case CENTER_RIGHT:
		p.setXY((wm.getView().getHorizontal() * (5.0f / 6.0f)), (wm.getView().getVertical() * (1.0f / 2.0f)));
		break;
	case BOTTOM_LEFT:
		p.setXY((wm.getView().getHorizontal() * (1.0f / 6.0f)), wm.getView().getVertical() - 1.0f);
		break;
	case BOTTOM_CENTER:
		p.setXY((wm.getView().getHorizontal() * (3.0f / 6.0f)), wm.getView().getVertical() - 1.0f);
		break;
	case BOTTOM_RIGHT:
		p.setXY((wm.getView().getHorizontal() * (5.0f / 6.0f)), wm.getView().getVertical() - 1.0f);
		break;
	default:
		LogManager::getInstance().writeLog("ViewObject::setLocation(): Invalid new location.");
	}
	if (!getBorder())
		y_delta = -1;
	p.setY(p.getY() + y_delta);
	setPosition(p);
	location = new_location;
}

df::ViewObjectLocation df::ViewObject::getLocation() const
{
	return location;
}

void df::ViewObject::setValue(int new_value)
{
	value = new_value;
}

int df::ViewObject::getValue() const
{
	return value;
}

void df::ViewObject::setBorder(bool display)
{
	if (border != display) {
		border = display;

		//Reset location
		setLocation(getLocation());
	}
}

bool df::ViewObject::getBorder() const
{
	return border;
}

void df::ViewObject::setColor(Color new_color)
{
	color = new_color;
}

df::Color df::ViewObject::getColor() const
{
	return color;
}

void df::ViewObject::setViewString(std::string new_view_string)
{
	view_string = new_view_string;
}

std::string df::ViewObject::getViewString() const
{
	return view_string;
}

void df::ViewObject::setDrawValue(bool new_draw_value)
{
	draw_value = new_draw_value;
}

bool df::ViewObject::getDrawValue() const
{
	return draw_value;
}
