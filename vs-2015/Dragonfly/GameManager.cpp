#if defined(_WIN32) || defined(_WIN64)
#include <Windows.h>
#endif
#include "LogManager.h"
#include "GameManager.h"
#include "WorldManager.h"
#include "GraphicsManager.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "ObjectListIterator.h"
#include "Clock.h"
#include "utility.h"

#include "EventStep.h"

df::GameManager::GameManager() {
	setType("GameManager");
	frame_time = FRAME_TIME_DEFAULT;
}
bool df::GameManager::isValid(std::string event_type)
{
	if (event_type == STEP_EVENT)
		return true;
	return false;
}
df::GameManager &df::GameManager::getInstance()
{
	static GameManager instance;
	return instance;
}

int df::GameManager::startUp()
{	
	LogManager &log_manager = LogManager::getInstance();
	log_manager.startUp();
	WorldManager &world_manager = WorldManager::getInstance();
	world_manager.startUp();
	GraphicsManager &graphics_manager = GraphicsManager::getInstance();
	graphics_manager.startUp();
	InputManager &input_manager = InputManager::getInstance();
	input_manager.startUp();
	ResourceManager &resource_manager = ResourceManager::getInstance();
	resource_manager.startUp();
	game_over = false;
#if defined(_WIN32) || defined(_WIN64)
	timeBeginPeriod(1);
#endif
	Manager::startUp();
	log_manager.writeLog("GameManager::startUp(): Successfully started up");
	return 0;
}

void df::GameManager::shutDown()
{
#if defined(_WIN32) || defined(_WIN64)
	timeEndPeriod(1);
#endif
	ResourceManager::getInstance().shutDown();
	InputManager::getInstance().shutDown();
	//Remove all objects
	WorldManager::getInstance().shutDown();
	//Shut down log manager
	LogManager::getInstance().shutDown();
	//Set game over to stop game loop
	setGameOver();
	Manager::shutDown();
}

void df::GameManager::run()
{
	LogManager &log_manager = LogManager::getInstance();
	WorldManager &world_manager = WorldManager::getInstance();
	GraphicsManager &graphics_manager = GraphicsManager::getInstance();
	InputManager &input_manager = InputManager::getInstance();
	int game_loop_count = 0;
	long int loop_time, intended_sleep_time, adjust_time = 0, actual_sleep_time;
	Clock clock;
	ObjectList world_objects;
	while (!game_over) {
		clock.delta();
		//Get input from keyboard/mouse
		input_manager.getInput();
		//Update world state
		EventStep s = EventStep(game_loop_count);
		onEvent(&s);
		world_manager.update();
		//Draw current scene to back buffer
		world_manager.draw();
		//Swap back buffer to current buffer
		graphics_manager.swapBuffers();
		loop_time = clock.split();
		intended_sleep_time = FRAME_TIME_DEFAULT - loop_time - adjust_time;
		clock.delta();
		if (intended_sleep_time > 0)
			sleep(intended_sleep_time);
		actual_sleep_time = clock.split();
		adjust_time = actual_sleep_time - intended_sleep_time;
		game_loop_count++;
	}
}

void df::GameManager::setGameOver(bool new_game_over)
{
	game_over = new_game_over;
}

bool df::GameManager::getGameOver() const
{
	return game_over;
}

int df::GameManager::getFrameTime() const
{
	return frame_time;
}
