#include "Sprite.h"

df::Sprite::~Sprite()
{
	if (frame != NULL) {
		delete [] frame;
	}
}

df::Sprite::Sprite(int max_frames)
{
	frame_count = 0;
	width = 0;
	height = 0;
	frame = new Frame[max_frames];
	max_frame_count = max_frames;
	color = COLOR_DEFAULT;
}

void df::Sprite::setWidth(int new_width)
{
	width = new_width;
}

int df::Sprite::getWidth() const
{
	return width;
}

void df::Sprite::setHeight(int new_height)
{
	height = new_height;
}

int df::Sprite::getHeight() const
{
	return height;
}

void df::Sprite::setColor(Color new_color)
{
	color = new_color;
}

df::Color df::Sprite::getColor() const
{
	return color;
}

int df::Sprite::getFrameCount() const
{
	return frame_count;
}

int df::Sprite::addFrame(Frame new_frame)
{
	if (frame_count == max_frame_count)
		return -1;
	else
		frame[frame_count++] = new_frame;
	return 0;
}

df::Frame df::Sprite::getFrame(int frame_number) const
{
	if ((frame_number < 0) || (frame_number >= frame_count)) {
		Frame empty;
		return empty;
	}
	return frame[frame_number];
}

void df::Sprite::setLabel(std::string new_label)
{
	label = new_label;
}

std::string df::Sprite::getLabel() const
{
	return label;
}
