#ifndef DEBUG_INFO_UPDATED_LISTENER_H
#define DEBUG_INFO_UPDATED_LISTENER_H

#ifdef DEBUG

#include "../../EventEngine/Event.hpp"
#include "../../EventEngine/EventListener.hpp"
#include "../../Engines/GraphicsEngine.hpp"
#include <string>

/**
* @author Kevin Guillaumond <kevin.guillaumond@gmail.com>
*/
class DebugInfoUpdatedListener : public EventListener
{
	public:
		DebugInfoUpdatedListener(GraphicsEngine* _graphicsEngine);

		/**
		* Called when an debug_info_updated event is dispatched
		* @param string eventType Type of received event
		* @param Event* event
		*/
		void onEvent(const std::string &_eventType, Event* _event);

	private:
		GraphicsEngine* m_graphicsEngine;
};

#endif

#endif // DEBUG_INFO_UPDATED_LISTENER_H
