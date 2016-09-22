#include "Music.h"

df::Music::Music()
{
}

int df::Music::loadMusic(std::string filename)
{
	if (!music.openFromFile(filename)) {
		return -1;
	}
	return 0;
}

void df::Music::setLabel(std::string new_label)
{
	label = new_label;
}

std::string df::Music::getLabel() const
{
	return label;
}

void df::Music::play(bool loop)
{
	music.setLoop(loop);
	music.play();
}

void df::Music::stop()
{
	music.stop();
}

void df::Music::pause()
{
	music.pause();
}

sf::Music * df::Music::getMusic()
{
	return &music;
}
