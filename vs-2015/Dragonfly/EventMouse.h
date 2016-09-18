#pragma once
#include "Event.h"
#include "Vector.h"

namespace df {
	const std::string EVENT_MOUSE = "df::Mouse";

	enum EventMouseAction {
		UNDEFINED_MOUSE_ACTION = -1,
		CLICKED = 0,
		PRESSED = 1,
		MOVED = 2,
		DOWN = 3
	};

	namespace Mouse {
		enum EventMouseButton {
			UNDEFINED_MOUSE_BUTTON = -1,
			LEFT,
			RIGHT,
			MIDDLE,
		};
	}

	class EventMouse : public Event {
	private:
		EventMouseAction mouse_action;					//mouse action
		Mouse::EventMouseButton mouse_button;					//mouse button
		Vector mouse_xy;								//mouse (x,y) coords
	public:
		EventMouse();
		//Set key in event
		void setMouseButton(Mouse::EventMouseButton new_button);
		//Get key from event
		Mouse::EventMouseButton getMouseButton() const;
		//Set keyboard event action
		void setMouseAction(EventMouseAction new_action);
		//Get keyboard event action
		EventMouseAction getMouseAction() const;
		//Set mouse position
		void setMousePosition(Vector new_mouse_xy);
		//Get mouse event's x,y position
		Vector getMousePosition() const;
	};
}
