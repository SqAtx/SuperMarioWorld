#ifndef FOREGROUND_ITEM_UPDATED_LISTENER_H
#define FOREGROUND_ITEM_UPDATED_LISTENER_H

#include "../EventEngine/Event.hpp"
#include "../EventEngine/EventListener.hpp"
#include "../../Game/GameEngine.hpp"
#include "../../Graphics/GraphicsEngine.hpp"
#include <string>

/**
* @author Kevin Guillaumond <kevin.guillaumond@gmail.com>
*/
class ForegroundItemUpdatedListener : public EventListener
{
public:
	ForegroundItemUpdatedListener(GameEngine* _gameEngine);
	ForegroundItemUpdatedListener(GraphicsEngine* _graphicsEngine);

	/**
	* Called when an foreground_item_updated event is dispatched
	* @param string eventType Type of received event
	* @param Event* event
	*/
	void onEvent(const std::string &_eventType, Event* _event);

private:
	GameEngine* m_gameEngine;
	GraphicsEngine* m_graphicsEngine;
};

#endif // FOREGROUND_ITEM_UPDATED_LISTENER_H
