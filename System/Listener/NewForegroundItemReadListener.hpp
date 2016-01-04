#ifndef NEW_FOREGROUND_ITEM_READ_LISTENER_H
#define NEW_FOREGROUND_ITEM_READ_LISTENER_H

#include "../EventEngine/Event.hpp"
#include "../EventEngine/EventListener.hpp"
#include "../../Game/GameEngine.hpp"
#include "../../Graphics/GraphicsEngine.hpp"
#include <string>

/**
* @author Kevin Guillaumond <kevin.guillaumond@gmail.com>
*/
class NewForegroundItemReadListener : public EventListener
{
	public:
		NewForegroundItemReadListener(GameEngine* _gameEngine);
		NewForegroundItemReadListener(GraphicsEngine* _graphicsEngine);

		/**
		* Called when an new_foreground_item_read event is dispatched
		* @param string eventType Type of received event
		* @param Event* event
		*/
		void onEvent(const std::string &_eventType, Event* _event);

private:
	GameEngine* m_gameEngine;
	GraphicsEngine* m_graphicsEngine;
};

#endif // NEW_FOREGROUND_ITEM_READ_LISTENER_H
