#pragma once
#include "Manager.h"
#include "JoystickList.h"
#include "JoystickListIterator.h"
//--Helpers to check input event--//
//Checks which key has been pressed
//Sends KeyboardEvent
void checkKeyPress();
//Checks which mouse button has been pressed
//Sends MouseEvent
void checkMousePress();
//Checks which joystick input 
//Sends JoystickEvent
void checkJoysickAxis();
void checkJoystickButton();
namespace df {
	class InputManager : public Manager {
	private:
		InputManager();
		InputManager(InputManager const&);
		void operator=(InputManager const&);
		bool joystickMode;
		JoystickList joysticks;
		bool isValid(std::string event_type);
	public:
		//Get instance of InputManager
		static InputManager &getInstance();
		//Get window ready to take in inputs	
		//Return 0, else return -1
		int startUp();
		//Revert back to normal window mode 
		void shutDown();
		//Get input from the keyboard and mouse
		//Pass event along to all objects
		void getInput();
		//Enable joystick input
		void enableJoystick(bool enabled);
		//Is joystick enabled
		bool isJoystickEnabled() const;
	};
}