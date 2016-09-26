#pragma once
#include "ViewObject.h"
enum AudioType {
	UNDEFINED = -1,
	SOUND,
	MUSIC
};
class AudioPrompt : public df::ViewObject {
private:
	std::string label;
	std::string key;
	AudioType type;
	df::Sound *sound;
	int timesPressed;
public:
	AudioPrompt(std::string new_label, std::string new_key, AudioType new_type);
	int eventHandler(const df::Event *p_e);
};