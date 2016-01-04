#ifndef FOREGROUND_ITEM_REMOVED_LISTENER_H
#define FOREGROUND_ITEM_REMOVED_LISTENER_H

#include "../EventEngine/Event.hpp"
#include "../EventEngine/EventListener.hpp"
#include "../../Graphics/GraphicsEngine.hpp"
#include <string>

/**
* @author Kevin Guillaumond <kevin.guillaumond@gmail.com>
*/
class ForegroundItemRemovedListener : public EventListener
{
public:
	ForegroundItemRemovedListener(GraphicsEngine* _graphicsEngine);

	/**
	* Called when an foreground_item_removed event is dispatched
	* @param string eventType Type of received event
	* @param Event* event
	*/
	void onEvent(const std::string &_eventType, Event* _event);

private:
	GraphicsEngine* m_graphicsEngine;
};

#endif // FOREGROUND_ITEM_REMOVED_LISTENER_H
