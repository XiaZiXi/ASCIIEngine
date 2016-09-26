#include <sstream>
#include "WorldManager.h"
#include "ResourceManager.h"
#include "AudioPrompt.h"
#include "EventKeyboard.h"
#include "EventView.h"
#include "EventAudioTrigger.h"

AudioPrompt::AudioPrompt(std::string new_label, std::string new_key, AudioType new_type)
{
	std::stringstream ss;
	key = new_key;
	label = new_label;
	type = new_type;
	ss << "Press " + key + " to play " + label + ".";
	setViewString(ss.str());
	switch (type) {
	case SOUND:
		df::Sound *s = df::ResourceManager::getInstance().getSound(label);
		if (s != NULL)
			sound = s;
		break;
	}
}

int AudioPrompt::eventHandler(const df::Event * p_e)
{
	ViewObject::eventHandler(p_e);
	if (p_e->getType() == EVENT_AUDIO_TRIGGER) {
		const EventAudioTrigger *p_at = dynamic_cast <const EventAudioTrigger *>(p_e);
		if (p_at->getKey() == key) {
			switch (type) {
			case SOUND:
				if (sound != NULL)
					sound->play();
				break;
			case MUSIC:
				df::Music *m = df::ResourceManager::getInstance().getMusic(label);
				if (m != NULL) {
					if (m->isPlaying()) {
						m->pause();
					}
					else {
						m->play();
					}
				}
				break;
			}
			
			df::EventView ev(getViewString(), 1, true);
			df::WorldManager::getInstance().onEvent(&ev);
			return 1;
		}
	}
	return 0;
}


