#include "EventKeyboard.h"

df::EventKeyboard::EventKeyboard()
{
	key_val = Keyboard::UNDEFINED_KEY;
	keyboard_action = EventKeyboardAction::UNDEFINED_KEYBOARD_ACTION;
	setType(KEYBOARD_EVENT);
}

void df::EventKeyboard::setKey(Keyboard::Key new_key)
{
	key_val = new_key;
}

df::Keyboard::Key df::EventKeyboard::getKey() const
{
	return key_val;
}

void df::EventKeyboard::setKeyboardAction(EventKeyboardAction new_action)
{
	keyboard_action = new_action;
}

df::EventKeyboardAction df::EventKeyboard::getKeyboardAction() const
{
	return keyboard_action;
}
