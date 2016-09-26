#pragma once
#include "ViewObject.h"
#include "Event.h"

namespace df {
	const std::string VIEW_EVENT = "df::view";
	class EventView : public Event {
	private:
		std::string tag;
		int value;
		bool delta;
	public:
		//Create event w/ tag VIEW_EVENT, value 0, and delta false
		EventView();

		//Create event w/ tag, value, and delta
		EventView(std::string new_tag, int new_value, bool new_delta);

		//Set/get tag
		void setTag(std::string new_tag);
		std::string getTag() const;

		//Set/get value
		void setValue(int new_value);
		int getValue() const;

		//Set/get delta 
		void setDelta(int new_delta);
		bool getDelta() const;
	};
}