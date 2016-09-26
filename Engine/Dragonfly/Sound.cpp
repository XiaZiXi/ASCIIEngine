#include "Sound.h"

df::Sound::Sound()
{
}

df::Sound::~Sound()
{
}

int df::Sound::loadSound(std::string filename)
{
	if (!sound_buffer.loadFromFile(filename)) {
		return -1;
	}
	sound.setBuffer(sound_buffer);
	return 0;
}

void df::Sound::setLabel(std::string new_label)
{
	label = new_label;
}

std::string df::Sound::getLabel() const
{
	return label;
}

void df::Sound::play(bool loop)
{
	sound.setLoop(loop);
	sound.play();
}

void df::Sound::stop()
{
	sound.stop();
}

void df::Sound::pause()
{
	sound.pause();
}

sf::Sound df::Sound::getSound() const
{
	return sound;
}
