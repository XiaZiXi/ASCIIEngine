#pragma once
#include <string>
#include "Object.h"
#include "Event.h"

namespace df {
	enum ViewObjectLocation {
		UNDEFINED = -1,
		TOP_LEFT,
		TOP_CENTER,
		TOP_RIGHT,
		CENTER_LEFT,
		CENTER_CENTER,
		CENTER_RIGHT,
		BOTTOM_LEFT,
		BOTTOM_CENTER,
		BOTTOM_RIGHT,
	};

	class ViewObject : public Object {
	private:
		std::string view_string;		//label for value
		int value;						//value of label
		bool draw_value;				//value displayed
		bool border;					//does this have a border
		Color color;					//color of view
		ViewObjectLocation location;	//location on screen
	public:
		//Construct ViewObject.
		//SPECTRAL & max alt
		//ViewObject defaults: border, top_center, default_color, draw_value
		ViewObject();

		//draw view obj
		virtual void draw();
		//event handler for view objects
		virtual int eventHandler(const Event *p_e);

		//Get/set location of view obj
		void setLocation(ViewObjectLocation new_location);
		ViewObjectLocation getLocation() const;
		//Get/set value of label
		void setValue(int new_value);
		int getValue() const;
		//Get/set whether or not border is displayed
		void setBorder(bool display = true);
		bool getBorder() const;
		//Get/color color
		void setColor(Color new_color);
		Color getColor() const;
		//Get/set view obj label
		void setViewString(std::string new_view_string);
		std::string getViewString() const;
		//Get/set draw value of display string
		void setDrawValue(bool new_draw_value = true);
		bool getDrawValue() const;
	};
}