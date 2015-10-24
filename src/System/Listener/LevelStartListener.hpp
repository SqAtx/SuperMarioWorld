#ifndef LEVEL_START_LISTENER_H
#define LEVEL_START_LISTENER_H

#include "../../EventEngine/Event.hpp"
#include "../../EventEngine/EventListener.hpp"
#include "../../Engines/SoundEngine.hpp"
#include <string>

/**
* @author Kevin Guillaumond <kevin.guillaumond@gmail.com>
*/
class LevelStartListener : public EventListener
{
public:
	LevelStartListener(SoundEngine* _soundEngine);

	/**
	* Called when an level_start event is dispatched
	* @param string eventType Type of received event
	* @param Event* event
	*/
	void onEvent(const std::string &_eventType, Event* _event);

private:
	SoundEngine* m_soundEngine;
};

#endif
