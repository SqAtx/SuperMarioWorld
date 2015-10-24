#ifndef MARIO_DEATH_LISTENER_H
#define MARIO_DEATH_LISTENER_H

#include "../../EventEngine/Event.hpp"
#include "../../EventEngine/EventListener.hpp"
#include "../../Engines/SoundEngine.hpp"
#include <string>

/**
* @author Kevin Guillaumond <kevin.guillaumond@gmail.com>
*/
class MarioDeathListener : public EventListener
{
	public:
		MarioDeathListener(SoundEngine* _soundEngine);

		/**
		* Called when an mario_death event is dispatched
		* @param string eventType Type of received event
		* @param Event* event
		*/
		void onEvent(const std::string &_eventType, Event* _event);

	private:
		SoundEngine* m_soundEngine;
};

#endif // MARIO_DEATH_LISTENER_H
