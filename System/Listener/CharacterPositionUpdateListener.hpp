#ifndef CHAR_POS_UPDATE_LISTENER_H
#define CHAR_POS_UPDATE_LISTENER_H

#include "../EventEngine/Event.hpp"
#include "../EventEngine/EventListener.hpp"
#include "../../Graphics/GraphicsEngine.hpp"
#include <string>

/**
* @author Kevin Guillaumond <kevin.guillaumond@gmail.com>
*/
class CharacterPositionUpdateListener : public EventListener
{
public:
	CharacterPositionUpdateListener(GraphicsEngine* _graphicsEngine);

	/**
	* Called when a character_position_updated event is dispatched
	* @param string eventType Type of received event
	* @param Event* event
	*/
	void onEvent(const std::string &_eventType, Event* _event);

private:
	GraphicsEngine* m_graphicsEngine;
};

#endif // CHAR_POS_UPDATE_LISTENER_H
