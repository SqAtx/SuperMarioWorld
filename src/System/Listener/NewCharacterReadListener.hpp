#ifndef NEW_CHARACTER_READ_LISTENER_H
#define NEW_CHARACTER_READ_LISTENER_H

#include "../../EventEngine/Event.hpp"
#include "../../EventEngine/EventListener.hpp"
#include "../../Engines/GameEngine.hpp"
#include <string>

/**
* @author Kevin Guillaumond <kevin.guillaumond@gmail.com>
*/
class NewCharacterReadListener : public EventListener
{
	public:
		NewCharacterReadListener(GameEngine* _gameEngine);

		/**
		* Called when an new_character_read event is dispatched
		* @param string eventType Type of received event
		* @param Event* event
		*/
		void onEvent(const std::string &_eventType, Event* _event);

	private:
		GameEngine* m_gameEngine;
};

#endif // NEW_CHARACTER_READ_LISTENER_H
