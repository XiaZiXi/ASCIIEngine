#include "GameManager.h"
#include "WorldManager.h"
#include "EventKeyboard.h"
#include "EventView.h"
#include "Player.h"
#include "EventAudioTrigger.h"

int Player::eventHandler(const df::Event * p_e)
{
	if (p_e->getType() == df::KEYBOARD_EVENT) {
		const df::EventKeyboard *p_ek = dynamic_cast <const df::EventKeyboard *>(p_e);
		if (p_ek->getKeyboardAction() != df::KEY_DOWN)
			return 0;
		std::string key;
		switch (p_ek->getKey()) {
		case df::Keyboard::NUM1:
			key = "1";
			break;
		case df::Keyboard::NUM2:
			key = "2";
			break;
		case df::Keyboard::NUM3:
			key = "3";
			break;
		case df::Keyboard::NUM4:
			key = "4";
			break;
		case df::Keyboard::NUM5:
			key = "5";
			break;
		case df::Keyboard::NUM6:
			key = "6";
			break;
		case df::Keyboard::NUM7:
			key = "7";
			break;
		case df::Keyboard::NUM8:
			key = "8";
			break;
		case df::Keyboard::NUM9:
			key = "9";
			break;
		case df::Keyboard::Q:			// quit
			df::WorldManager &world_manager = df::WorldManager::getInstance();
			world_manager.markForDelete(this);
			df::GameManager::getInstance().setGameOver();
			break;
		}
		EventAudioTrigger eat(key);
		df::WorldManager::getInstance().onEvent(&eat);
	}
	return 0;
}
