#pragma once
#include "EventView.h"

const std::string EVENT_AUDIO_TRIGGER = "AUDIOTRIGGER";
class EventAudioTrigger : public df::Event {
private:
	std::string key;
public:
	EventAudioTrigger(std::string new_key);
	std::string getKey() const;
};