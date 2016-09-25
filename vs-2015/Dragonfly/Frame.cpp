#include "Frame.h"

df::Frame::Frame()
{
	width = 0;
	height = 0;
	frame_str = "";
}

df::Frame::Frame(int new_width, int new_height, std::string new_frame_str)
{
	width = new_width;
	height = new_height;
	frame_str = new_frame_str;
}

void df::Frame::setWidth(int new_width)
{
	width = new_width;
}

int df::Frame::getWidth() const
{
	return width;
}

void df::Frame::setHeight(int new_height)
{
	height = new_height;
}

int df::Frame::getHeight() const
{
	return height;
}

void df::Frame::setString(std::string new_frame_str)
{
	frame_str = new_frame_str;
}

std::string df::Frame::getString() const
{
	return frame_str;
}
