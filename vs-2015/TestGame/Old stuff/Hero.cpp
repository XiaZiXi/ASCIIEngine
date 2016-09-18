#include <stdlib.h>
#include "LogManager.h"
#include "WorldManager.h"
#include "GameManager.h"
#include "GraphicsManager.h"
#include "EventStep.h"
#include "EventKeyboard.h"
#include "EventMouse.h"

#include "Hero.h"
#include "EventOut.h"

void Hero::handleKey(df::EventKeyboard * p_k)
{
	df::LogManager &log_manager = df::LogManager::getInstance();
	switch (p_k->getKey())
	{
	case df::Keyboard::A:
		log_manager.writeLog("A pressed");
		break;
	case df::Keyboard::Q:
		df::GameManager &game_manager = df::GameManager::getInstance();
		game_manager.setGameOver();
		break;
	}
}

void Hero::handleMouse(df::EventMouse * p_m)
{
	df::LogManager &log_manager = df::LogManager::getInstance();
	switch (p_m->getMouseButton())
	{
	case df::EventMouseButton::LEFT:
		log_manager.writeLog("Left pressed at %f, %f", p_m->getMousePosition().getX(), p_m->getMousePosition().getY());
		break;
	case df::EventMouseButton::RIGHT:
		log_manager.writeLog("Right pressed at %f, %f", p_m->getMousePosition().getX(), p_m->getMousePosition().getY());
		break;
	case df::EventMouseButton::MIDDLE:
		log_manager.writeLog("Middle pressed at %f, %f", p_m->getMousePosition().getX(), p_m->getMousePosition().getY());
		break;
	}
}

void Hero::handleJoystick(df::EventJoystick * p_j)
{
}

Hero::Hero() {
	df::LogManager &log_manager = df::LogManager::getInstance();
	//Set position to middle of screen
	setType("Hero");
	df::Vector p(1.0f, 2.0f);
	setPosition(p);
	log_manager.writeLog("%d Hero::Hero(): Created %s at position %f, %f", getId(), getType().c_str(), getPosition().getX(), getPosition().getY());
	timeToDie = 5;
	setVelocity(df::Vector(-0.25f, 0.0f));
}

Hero::~Hero() {}

int Hero::eventHandler(const df::Event *p_e) {
	df::LogManager &log_manager = df::LogManager::getInstance();
	if (p_e->getType() == df::STEP_EVENT) {
		log_manager.writeLog("%d %s::eventHandler(): Step event received.", getId(), getType().c_str());
		//df::Vector p(std::rand() % 100, std::rand() % 100);
		//setPosition(p);
		//log_manager.writeLog("%d %s::eventHandler(): Assigned new position at %f, %f", getId(), getType().c_str(), getPosition().getX(), getPosition().getY());
		//every 5 seconds spawn
		return 1;
	}
	if (p_e->getType() == df::KEYBOARD_EVENT) {
		df::EventKeyboard *p_k = (df::EventKeyboard *)p_e;

		if (p_k->getKeyboardAction() == df::KEY_PRESSED) {
			log_manager.writeLog("HERO: KEY_PRESSED");
			handleKey(p_k);
		}
		else if (p_k->getKeyboardAction() == df::KEY_RELEASED){
			log_manager.writeLog("HERO: KEY_RELEASED");
			handleKey(p_k);
		}
	}
	if (p_e->getType() == df::EVENT_MOUSE) {
		df::EventMouse *p_m = (df::EventMouse *)p_e;

		if (p_m->getMouseAction() == df::EventMouseAction::PRESSED) {
			log_manager.writeLog("HERO: MOUSE PRESSED");
			handleMouse(p_m);
		}
	}
	if (p_e->getType() == df::OUT_EVENT) {
		df::GraphicsManager &gm = df::GraphicsManager::getInstance();
		df::Vector pos(gm.getHorizontal(), getPosition().getY());
		setPosition(pos);
	}

	return 0;
}

void Hero::draw() {
	df::GraphicsManager &graphics_manager = df::GraphicsManager::getInstance();
	df::Vector pos = getPosition();
	graphics_manager.drawCh(pos, 'A', df::BLUE);
}
