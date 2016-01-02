#ifndef KEYBOARD_LISTENER_H
#define KEYBOARD_LISTENER_H

#include "../../EventEngine/KeyboardEvent.hpp"
#include "../../EventEngine/EventListener.hpp"
#include "../../Engines/GameEngine.hpp"
#include <string>

/**
* @author Kevin Guillaumond
*/
class KeyboardListener : public EventListener
{
public:

	KeyboardListener(GameEngine* _gameEngine);

	/**
	* Called when a KeyboardEvent is dispached
	* @param string eventType Type of received event
	* @param Event* event
	*/
	void onEvent(const std::string &_eventType, Event* _event);

private:

	GameEngine* m_gameEngine;
};

#endif // KEYBOARD_LISTENER_H
