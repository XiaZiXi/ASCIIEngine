#pragma once
#include <string>

#include "Frame.h"
#include "Color.h"

namespace df {
	class Sprite {
	private:
		int width;
		int height;
		int max_frame_count;
		int frame_count;
		Color color;
		Frame *frame;
		std::string label;
		Sprite();

	public:
		//Destroy sprite, deleting any allocated frames
		~Sprite();
		//Create sprite with indicated maximum number of frames
		Sprite(int max_frames);
		//Set width of sprite
		void setWidth(int new_width);
		//Get width of sprite
		int getWidth() const;
		//Set height of sprite
		void setHeight(int new_height);
		//Get height of sprite
		int getHeight() const;
		//Set color of sprite
		void setColor(Color new_color);
		//Get color of sprite
		Color getColor() const;
		//Get total count of frames in sprite
		int getFrameCount() const;
		//Add frame to sprite
		//Return -1 if frame array is full, else 0
		int addFrame(Frame new_frame);
		//Get next sprite frame indicated by number
		//Return empty frame if out of range [0, frame_count]
		Frame getFrame(int frame_number) const;
		//Set label of sprite
		void setLabel(std::string new_label);
		//Get label of sprite
		std::string getLabel() const;
	};
}