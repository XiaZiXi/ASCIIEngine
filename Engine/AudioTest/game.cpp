//
// game.cpp
// 
#define GAME_NAME "Game"
#define VERSION 1.0

// Engine includes.
#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "AudioPrompt.h"
#include "Player.h"
 
// Game includes.

// Function prototypes.
void populateWorld(void);

void loadResources(void);
 
int main(int argc, char *argv[]) {
  df::LogManager &log_manager = df::LogManager::getInstance();

  // Start up game manager.
  df::GameManager &game_manager = df::GameManager::getInstance();
  if (game_manager.startUp())  {
    log_manager.writeLog("Error starting game manager!");
    game_manager.shutDown();
    return 0;
  }

  // Write game version information to logfile.
  log_manager.writeLog("%s, version %0.1f", GAME_NAME, VERSION);

  // Set flush of logfile during development (when done, make false).
  log_manager.setFlush(true);

  loadResources();

  // Setup some objects.
  populateWorld();
 
  // Run game (this blocks until game loop is over).
  game_manager.run();
 
  // Shut everything down.
  game_manager.shutDown();
}

void loadResources(void) {
	df::ResourceManager &rm = df::ResourceManager::getInstance();
	rm.loadSound("sounds/explode.wav", "explosion");
	rm.loadSound("sounds/fire.wav", "fire");
	rm.loadSound("sounds/hit.wav", "hit");
	rm.loadSound("sounds/missile.wav", "missile");
	rm.loadSound("sounds/missile-pickup.wav", "missile-pickup");
	rm.loadSound("sounds/nuke.wav", "nuke");
	rm.loadSound("sounds/nuke-pickup.wav", "nuke-pickup");
	rm.loadMusic("sounds/start-music.wav", "start-music");
	rm.loadMusic("sounds/game-over.wav", "game-over");
}
 
// Populate world with some objects.
void populateWorld(void) {
	new Player();
	AudioPrompt *p_ap = new AudioPrompt("explosion", "1", SOUND);
	p_ap->setValue(0);
	p_ap->setLocation(df::TOP_LEFT);
	p_ap->setColor(df::GREEN);
	AudioPrompt *p_ap2 = new AudioPrompt("fire", "2", SOUND);
	p_ap2->setValue(0);
	p_ap2->setLocation(df::TOP_CENTER);
	p_ap2->setColor(df::YELLOW);
	AudioPrompt *p_ap3 = new AudioPrompt("hit", "3", SOUND);
	p_ap3->setValue(0);
	p_ap3->setLocation(df::TOP_RIGHT);
	p_ap3->setColor(df::RED);
	AudioPrompt *p_ap4 = new AudioPrompt("missile", "4", SOUND);
	p_ap4->setValue(0);
	p_ap4->setLocation(df::CENTER_LEFT);
	p_ap4->setColor(df::CYAN);
	AudioPrompt *p_ap5 = new AudioPrompt("missile-pickup", "5", SOUND);
	p_ap5->setValue(0);
	p_ap5->setLocation(df::CENTER_CENTER);
	p_ap5->setColor(df::BLUE);
	AudioPrompt *p_ap6 = new AudioPrompt("nuke", "6", SOUND);
	p_ap6->setValue(0);
	p_ap6->setLocation(df::CENTER_RIGHT);
	p_ap6->setColor(df::MAGENTA);
	AudioPrompt *p_ap7 = new AudioPrompt("nuke-pickup", "7", SOUND);
	p_ap7->setValue(0);
	p_ap7->setLocation(df::BOTTOM_LEFT);
	p_ap7->setColor(df::WHITE);
	AudioPrompt *p_ap8 = new AudioPrompt("game-over", "8", MUSIC);
	p_ap8->setValue(0);
	p_ap8->setLocation(df::BOTTOM_CENTER);
	p_ap8->setColor(df::YELLOW);
	AudioPrompt *p_ap9 = new AudioPrompt("start-music", "9", MUSIC);
	p_ap9->setValue(0);
	p_ap9->setLocation(df::BOTTOM_RIGHT);
	p_ap9->setColor(df::CYAN);
}
