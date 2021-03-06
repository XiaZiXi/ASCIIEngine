#include <iostream>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Joystick.hpp>
#include "LogManager.h"
#include "WorldManager.h"
#include "GraphicsManager.h"
#include "InputManager.h"
#include "EventKeyboard.h"
#include "EventMouse.h"
#include "EventJoystick.h"

df::InputManager::InputManager() {
	joystickMode = false;
}

bool df::InputManager::isValid(std::string event_type)
{
	if (event_type == KEYBOARD_EVENT)
		return true;
	else if (event_type == EVENT_MOUSE)
		return true;
	else if (event_type == JOYSTICK_EVENT)
		return true;
	else
		return false;
}

df::InputManager & df::InputManager::getInstance()
{
	static InputManager instance;
	return instance;
}

int df::InputManager::startUp()
{
	GraphicsManager &graphics_manager = GraphicsManager::getInstance();
	if (!graphics_manager.isStarted()) {
		return -1;
	}

	sf::RenderWindow *window = graphics_manager.getWindow();
	window->setKeyRepeatEnabled(false);
	Manager::startUp();
	return 0;
}

void df::InputManager::shutDown()
{
	GraphicsManager &graphics_manager = GraphicsManager::getInstance();
	if (!graphics_manager.isStarted()) {
		return;
	}

	sf::RenderWindow *window = graphics_manager.getWindow();
	window->setKeyRepeatEnabled(true);
	Manager::shutDown();
}

void df::InputManager::getInput()
{
	GraphicsManager &graphics_manager = GraphicsManager::getInstance();
	WorldManager &world_manager = WorldManager::getInstance();
	LogManager &log_manager = LogManager::getInstance();
	sf::RenderWindow *window = graphics_manager.getWindow();
	sf::Event event;
	while (window->pollEvent(event)) {
		if (event.type == sf::Event::KeyPressed) {
			EventKeyboard e = EventKeyboard();
			e.setKeyboardAction(EventKeyboardAction::KEY_DOWN);
			e.setKey((df::Keyboard::Key)event.key.code);
			//send EventKeyboard to all objects
			onEvent(&e);
		}
		else if (event.type == sf::Event::KeyReleased) {
			EventKeyboard e = EventKeyboard();
			e.setKeyboardAction(EventKeyboardAction::KEY_RELEASED);
			e.setKey((df::Keyboard::Key)event.key.code);
			onEvent(&e);
			EventKeyboard ev = EventKeyboard();
			ev.setKeyboardAction(EventKeyboardAction::KEY_PRESSED);
			ev.setKey((df::Keyboard::Key)event.key.code);
			//send EventKeyboard to all objects
			onEvent(&ev);
		}
		else if (event.type == sf::Event::MouseMoved) {
			sf::Vector2i pos = sf::Mouse::getPosition(*(window));
			EventMouse e = EventMouse();
			e.setMouseAction(EventMouseAction::MOVED);
			e.setMousePosition(df::Vector((float)pos.x, (float)pos.y));
			onEvent(&e);
		}
		else if (event.type == sf::Event::MouseButtonPressed) {
			sf::Vector2i pos = sf::Mouse::getPosition(*(window));
			EventMouse e = EventMouse();
			e.setMouseAction(EventMouseAction::PRESSED);
			e.setMouseButton((df::Mouse::EventMouseButton)event.mouseButton.button);
			e.setMousePosition(df::Vector((float)pos.x, (float)pos.y));
			onEvent(&e);
			EventMouse ev = EventMouse();
			ev.setMouseAction(EventMouseAction::CLICKED);
			ev.setMouseButton((df::Mouse::EventMouseButton)event.mouseButton.button);
			ev.setMousePosition(df::Vector((float)pos.x, (float)pos.y));
			onEvent(&ev);
		}
		if (joystickMode) {
			if (event.type == sf::Event::JoystickConnected) {
				unsigned int id = event.joystickConnect.joystickId;
				//send event and initialize its joystick obj
				joysticks.getJoystickAt(id)->setConnection(true);
				std::cout << id + "connected" << std::endl;
				EventJoystick e;
				e.setJoystick(id);
				e.setConnection(JoystickConnection::CONNECT);
				onEvent(&e);
			}
			else if (event.type == sf::Event::JoystickDisconnected) {
				unsigned int id = event.joystickConnect.joystickId;
				//send event and un-initialize its joystick obj
				joysticks.getJoystickAt(id)->setConnection(false);
				std::cout << id + "disconnected" << std::endl;
				EventJoystick e;
				e.setJoystick(id);
				e.setConnection(JoystickConnection::DISCONNECT);
				onEvent(&e);
			}
			else if (event.type == sf::Event::JoystickButtonPressed) {
				unsigned int id = event.joystickButton.joystickId;
				unsigned int button = event.joystickButton.button;
				std::cout << button << std::endl;
				EventJoystick e = EventJoystick();
				e.setJoystick(id);
				e.setJoystickButtonAction(JoysickButton::PRESSED);
				e.setJoystickButton(button);
				onEvent(&e);
			}
			else if (event.type == sf::Event::JoystickButtonReleased) {
				unsigned int id = event.joystickButton.joystickId;
				unsigned int button = event.joystickButton.button;
				EventJoystick e = EventJoystick();
				e.setJoystick(id);
				e.setJoystickButtonAction(JoysickButton::RELEASED);
				e.setJoystickButton(button);
				onEvent(&e);
			}
			else if (event.type == sf::Event::JoystickMoved) {
				unsigned int id = event.joystickMove.joystickId;
				sf::Joystick::Axis axis = event.joystickMove.axis;
				float pos = event.joystickMove.position;
				std::cout << pos << std::endl;
				EventJoystick e = EventJoystick();
				e.setJoystick(id);
				e.setJoystickAxis((JoystickAxis::EventJoystickAxis)axis);
				e.setAxisPosition(pos);
				onEvent(&e);
			}
		}
	}

	//Check current key presses for each individual key
	//checkKeyPress();
	//Check current mouse press events for each position
	//checkMousePress();
	if (joystickMode) {
		checkJoysickAxis();
		checkJoystickButton();
	}
}

void df::InputManager::enableJoystick(bool enabled)
{
	joystickMode = enabled;
}

bool df::InputManager::isJoystickEnabled() const
{
	return joystickMode;
}

void checkKeyPress() {
	df::WorldManager &world_manager = df::WorldManager::getInstance();
	for (int k = 0; k < sf::Keyboard::KeyCount; k++) {
		if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)k)) {
			//create event keyboard of this key and action
			df::EventKeyboard e = df::EventKeyboard();
			e.setKeyboardAction(df::EventKeyboardAction::KEY_DOWN);
			e.setKey((df::Keyboard::Key)k);
			//send EventKeyboard to all objects
			df::InputManager::getInstance().onEvent(&e);
			break;
		}
	}
}

void checkMousePress() {
	df::GraphicsManager &graphics_manager = df::GraphicsManager::getInstance();
	df::WorldManager &world_manager = df::WorldManager::getInstance();
	sf::RenderWindow *window = graphics_manager.getWindow();
	for (int mb = 0; mb < sf::Mouse::ButtonCount; mb++) {
		if (sf::Mouse::isButtonPressed((sf::Mouse::Button)mb)) {
			sf::Vector2i pos = sf::Mouse::getPosition(*(window));
			df::EventMouse e = df::EventMouse();
			e.setMouseAction(df::EventMouseAction::PRESSED);
			e.setMouseButton((df::Mouse::EventMouseButton)mb);
			e.setMousePosition(df::Vector((float)pos.x, (float)pos.y));
			df::InputManager::getInstance().onEvent(&e);
			df::EventMouse ev = df::EventMouse();
			ev.setMouseAction(df::EventMouseAction::CLICKED);
			ev.setMouseButton((df::Mouse::EventMouseButton)mb);
			ev.setMousePosition(df::Vector((float)pos.x, (float)pos.y));
			df::InputManager::getInstance().onEvent(&e);
			break;
		}
	}
}

void checkJoysickAxis() {
	//do same as above 
}

void checkJoystickButton() {
	//do same as above
}
