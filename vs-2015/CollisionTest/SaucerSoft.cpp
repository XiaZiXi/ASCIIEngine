//
// Saucer.cpp
//
 
#include <stdlib.h>		// for rand()

// Engine includes.
#include "EventCollision.h"
#include "EventOut.h"
#include "GraphicsManager.h"
#include "LogManager.h"
#include "WorldManager.h"
 
// Game includes.
#include "SaucerSoft.h"
#include "Saucer.h"

SaucerSoft::SaucerSoft() {
  df::LogManager &log_manager = df::LogManager::getInstance();

  // Set object type.
  setType("SaucerSoft");
  setSolidness(df::SOFT);
  setAltitude(0);
}

// Handle event.
// Return 0 if ignored, else 1.
int SaucerSoft::eventHandler(const df::Event *p_e) {

  if (p_e->getType() == df::OUT_EVENT) {
    out();
    return 1;
  }

  if (p_e->getType() == df::COLLISION_EVENT) {
    const df::EventCollision *p_collision_event = dynamic_cast <const df::EventCollision *> (p_e);
    hit(p_collision_event);
    return 1;
  }
 
  // If get here, have ignored this event.
  return 0;
}

// If moved off left edge, move back to far right.
void SaucerSoft::out() {

  // If haven't moved off left edge, then nothing to do.
  if (getPosition().getX() >= 0)
    return;

  // Otherwise, move back to far right.
  moveToStart();

}

// If saucer and player collide, mark both for deletion.
void SaucerSoft::hit(const df::EventCollision *p_c) {

  // If Saucer on Saucer, ignore.
	if (p_c->getObject1()->getType() == "Saucer"){
		((Saucer *)p_c->getObject1())->setColor(df::CYAN);
		return;
	}
	else if (p_c->getObject2()->getType() == "Saucer") {
		((Saucer *)p_c->getObject1())->setColor(df::CYAN);
		return;
	}

  // If Hero, mark both objects for destruction.
  if (((p_c -> getObject1() -> getType()) == "Hero") || 
      ((p_c -> getObject2() -> getType()) == "Hero")) {
	  df::LogManager::getInstance().writeLog("Collided with %s at %d, %d!", "Hero", p_c->getPosition().getX(), p_c->getPosition().getY());
  }

}

// Move saucer to starting location on right side of screen.
void SaucerSoft::moveToStart() {
}

void SaucerSoft::draw() {
  df::GraphicsManager &graphics_manager = df::GraphicsManager::getInstance();
  graphics_manager.drawCh(getPosition(), SAUCERSOFT_CHAR, df::CYAN); 
}
