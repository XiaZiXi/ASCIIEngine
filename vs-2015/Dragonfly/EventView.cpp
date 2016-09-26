#include "EventView.h"

df::EventView::EventView()
{
	setType(VIEW_EVENT);
	tag = VIEW_EVENT;
	value = 0;
	delta = false;
}

df::EventView::EventView(std::string new_tag, int new_value, bool new_delta)
{
	setType(VIEW_EVENT);
	tag = new_tag;
	value = new_value;
	delta = new_delta;
}

void df::EventView::setTag(std::string new_tag)
{
	tag = new_tag;
}

std::string df::EventView::getTag() const
{
	return tag;
}

void df::EventView::setValue(int new_value)
{
	value = new_value;
}

int df::EventView::getValue() const
{
	return value;
}

void df::EventView::setDelta(int new_delta)
{
	delta = new_delta;
}

bool df::EventView::getDelta() const
{
	return delta;
}
