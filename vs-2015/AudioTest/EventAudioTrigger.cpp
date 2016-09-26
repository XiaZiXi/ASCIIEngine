#include "EventAudioTrigger.h"

EventAudioTrigger::EventAudioTrigger(std::string new_key)
{
	setType(EVENT_AUDIO_TRIGGER);
	key = new_key;
}

std::string EventAudioTrigger::getKey() const
{
	return key;
}
