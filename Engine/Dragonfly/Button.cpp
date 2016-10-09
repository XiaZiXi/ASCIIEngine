#include "LogManager.h"
#include "WorldManager.h"
#include "InputManager.h"
#include "EventStep.h"
#include "utility.h"
#include "Button.h"

df::Button::Button()
{
	setType("Button");
	setButtonColor(df::COLOR_DEFAULT);
	setHighlightColor(df::RED);
	setColor(buttonColor);
	registerInterest(df::EVENT_MOUSE);
	buttonCooldown = 33;
	buttonCountdown = buttonCooldown;
}

df::Color df::Button::getButtonColor() const
{
	return buttonColor;
}

void df::Button::setButtonColor(df::Color new_color)
{
	buttonColor = new_color;
}

df::Color df::Button::getHighlightColor() const
{
	return highlightColor;
}

void df::Button::setHighlightColor(df::Color new_color)
{
	highlightColor = new_color;
}

bool df::Button::mouseOverButton(df::Vector pos) const
{
	int width = getViewString().size();
	int height = 1;
	if (getBorder()) {
		width += 4;
		height += 2;
	}
	df::Vector corner(getPosition().getX() - (width / 2),
		getPosition().getY() - (height / 2));
	df::Box b(corner, width, height - 1);
	if (pointIntersectsBox(pos, b))
		return true;
	else
		return false;
}

int df::Button::eventHandler(const df::Event * p_e)
{
	if (p_e->getType() == df::EVENT_MOUSE) {
		const df::EventMouse * p_m = dynamic_cast<const df::EventMouse *>(p_e);
		if (mouseOverButton(p_m->getMousePosition())) {
			setColor(highlightColor);
			if (p_m->getMouseAction() == df::CLICKED)
				callback(0);
		}
		else
			setColor(buttonColor);
	}

	return 1;
}