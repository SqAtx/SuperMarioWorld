#ifndef TOGGLE_IGNORE_INPUT_LISTENER_H
#define TOGGLE_IGNORE_INPUT_LISTENER_H

#include "../EventEngine/Event.hpp"
#include "../EventEngine/EventListener.hpp"
#include "../../Game/GameEngine.hpp"
#include <string>

/**
* @author Kevin Guillaumond <kevin.guillaumond@gmail.com>
* User input can be ignored for a short period of time (e.g. when Mario dies)
*/
class ToggleIgnoreInputListener : public EventListener
{
public:

	ToggleIgnoreInputListener(GameEngine* _gameEngine);

	/**
	* Called when an ToggleIgnoreInput is dispatched
	* @param string eventType Type of received event
	* @param Event* event
	*/
	void onEvent(const std::string &_eventType, Event* _event);

private:

	GameEngine* m_gameEngine;
};

#endif // TOGGLE_IGNORE_INPUT_LISTENER_H
