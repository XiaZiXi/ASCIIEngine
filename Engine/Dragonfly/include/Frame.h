#pragma once
#include <string>

namespace df {
	class Frame {
	private:
		int width;
		int height;
		std::string frame_str;

	public:
		//Create empty frame
		Frame();
		//Create frame of indicated width and height and string
		Frame(int new_width, int new_height, std::string new_frame_str);
		//Set width of frame
		void setWidth(int new_width);
		//Get width of frame
		int getWidth() const;
		//Set width of frame
		void setHeight(int new_height);
		//Get width of frame
		int getHeight() const;

		//Set frame characters stored as string
		void setString(std::string new_frame_str);
		//Get frame characters stored as string
		std::string getString() const;
	};
}