//
// Hero.cpp
//

// Engine includes.
#include "EventMouse.h"
#include "EventStep.h"
#include "GraphicsManager.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include "Sprite.h"
// Game includes.
#include "Hero.h"
#include "Saucer.h"
#include "SaucerSoft.h"

Hero::Hero() {

  df::LogManager &log_manager = df::LogManager::getInstance();

  // Player controls hero, so register with keyboard and mouse.
  registerInterest(df::KEYBOARD_EVENT);
  registerInterest(df::EVENT_MOUSE);

  // Need to update fire rate control each step.
  registerInterest(df::STEP_EVENT);

  // Set object type.
  setType("Hero");
  df::Sprite *h = df::ResourceManager::getInstance().getSprite("ship");
  if (h != NULL) {
	  setSprite(h);
	  setSpriteSlowdown(5);
	  setTransparency(); //Transparent sprite
  }
  // Set starting location.
  df::GraphicsManager &graphics_manager = df::GraphicsManager::getInstance();
  df::Vector pos(7.0f, graphics_manager.getVertical()/2.0f);
  setPosition(pos);

  p_reticle = new Reticle;
}

Hero::~Hero() {
	df::GameManager::getInstance().setGameOver();
}

// Handle event.
// Return 0 if ignored, else 1.
int Hero::eventHandler(const df::Event *p_e) {

  if (p_e->getType() == df::KEYBOARD_EVENT) {
    const df::EventKeyboard *p_keyboard_event = dynamic_cast <const df::EventKeyboard *> (p_e);
    kbd(p_keyboard_event);
    return 1;
  }

  if (p_e->getType() == df::EVENT_MOUSE) {
    const df::EventMouse *p_mouse_event = dynamic_cast <const df::EventMouse *> (p_e);
    mouse(p_mouse_event);
    return 1;
  }

  // If get here, have ignored this event.
  return 0;
}

// Take appropriate action according to mouse action.
void Hero::mouse(const df::EventMouse *p_mouse_event) {

  // Pressed button?
  if ((p_mouse_event->getMouseAction() == df::CLICKED) &&
      (p_mouse_event->getMouseButton() == df::Mouse::LEFT))
    fire(p_mouse_event->getMousePosition());
}

// Take appropriate action according to key pressed.
void Hero::kbd(const df::EventKeyboard *p_keyboard_event) {
  df::WorldManager &world_manager = df::WorldManager::getInstance();
  switch(p_keyboard_event->getKey()) {
  case df::Keyboard::W:			// up
	  df::LogManager::getInstance().writeLog("KEYPRESS W");
    if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN)
      move(0, -1);
    break;
  case df::Keyboard::S:			// down
	  df::LogManager::getInstance().writeLog("KEYPRESS S");
    if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN)
      move(0, +1);
    break;
  case df::Keyboard::A:			// down
	  df::LogManager::getInstance().writeLog("KEYPRESS A");
	  if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN)
		  move(-1, 0);
	  break;
  case df::Keyboard::D:			// down
	  df::LogManager::getInstance().writeLog("KEYPRESS D");
	  if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN)
		  move(+1, 0);
	  break;
  case df::Keyboard::Q:			// quit
    if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
      df::WorldManager &world_manager = df::WorldManager::getInstance();
      world_manager.markForDelete(this);
    }
    break;
  };

  return;
}

// Move up or down.
void Hero::move(int dx, int dy) {
	df::LogManager::getInstance().writeLog("move %d %d", dx, dy);
  df::GraphicsManager &graphics_manager = df::GraphicsManager::getInstance();
  df::WorldManager &world_manager = df::WorldManager::getInstance();
  df::Vector new_pos(getPosition().getX() + dx, getPosition().getY() + dy);

  // If stays on screen, allow move.
  if ((new_pos.getY() >= 0) && 
        (new_pos.getY() < graphics_manager.getVertical()) &&
		(new_pos.getX() >= 0) &&
		(new_pos.getX() < graphics_manager.getHorizontal())
	  )
      world_manager.moveObject(this, new_pos);
}

// Fire bullet towards target.
void Hero::fire(df::Vector target) {
	df::LogManager::getInstance().writeLog("Placed object at %f f", target.getX(), target.getY());
	SaucerSoft *s = new SaucerSoft;
	s->setPosition(target);
}
