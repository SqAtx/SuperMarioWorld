#ifndef GOT_LEVEL_INFO_LISTENER_H
#define GOT_LEVEL_INFO_LISTENER_H

#include "../EventEngine/Event.hpp"
#include "../EventEngine/EventListener.hpp"
#include "../../Game/GameEngine.hpp"
#include "../../Graphics/GraphicsEngine.hpp"
#include <string>

/**
* @author Kevin Guillaumond <kevin.guillaumond@gmail.com>
*/
class GotLevelInfoListener : public EventListener
{
public:
	GotLevelInfoListener(GameEngine* _gameEngine);
	GotLevelInfoListener(GraphicsEngine* _graphicsEngine);

	/**
	* Called when an mario_kicks_enemy event is dispatched
	* @param string eventType Type of received event
	* @param Event* event
	*/
	void onEvent(const std::string &_eventType, Event* _event);

private:
	GameEngine* m_gameEngine;
	GraphicsEngine* m_graphicsEngine;
};

#endif // GOT_LEVEL_INFO_LISTENER_H
