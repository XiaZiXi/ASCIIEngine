#pragma once
#include "Manager.h"

const std::string FRAME_TIME_TOKEN = "frame_time";

namespace df {
	//Default game loop time in ms. (33ms == 30fps)
	const int FRAME_TIME_DEFAULT = 33;
	class GameManager : public Manager {
	private:
		//Methods to ensure singleton
		GameManager();
		GameManager(GameManager const&);
		void operator=(GameManager const&);
		//Is the game currently gameover?
		bool game_over;
		//Target time for game loop
		int frame_time;
		bool isValid(std::string event_type);
		int parseConfig();
	public:
		//Get instance of GameManager
		static GameManager &getInstance();
		//Starts up GameManager. Returns 0 if successful
		//Starts up the Log and World managers
		int startUp();
		//Shuts down GameManager and closes the program
		void shutDown();
		//Run game loop
		void run();
		//Set Game Over status. If true, this will stop the game loop
		void setGameOver(bool new_game_over = true);
		//Get Game Over status
		bool getGameOver() const;
		//Return frame time
		//Target time for game loop in ms
		int getFrameTime() const;
	};
}