//
// game.cpp
// 

#include <Windows.h>
// Engine includes.
#include "LogManager.h"
#include "GameManager.h"
#include "WorldManager.h"
#include "utility.h"
#include "ObjectListIterator.h"
#include "Object.h"
#include "Hero.h"
#include "Star.h"
#include "GraphicsManager.h"
#include "InputManager.h"
#include "JoystickFriend.h"
void populateWorld(void);

int main(int argc, char *argv[]) {
	df::LogManager &log_manager = df::LogManager::getInstance();
	//Start up game manager.
	df::GameManager &game_manager = df::GameManager::getInstance();
	if (game_manager.startUp()) {
		log_manager.writeLog("Error starting game manager!");
		game_manager.shutDown();
		return 0;
	}

	// Set flush of logfile during development (when done, make false).
	log_manager.setFlush(true);
	populateWorld();

	game_manager.run(); //start the game
	game_manager.shutDown();

	return 0;
}

void populateWorld(void) {
	for (int i = 0; i < 16; i++)
		new Star;
	new Hero;
}