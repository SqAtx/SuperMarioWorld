#ifndef MARIO_KICKED_ENEMY_LISTENER_H
#define MARIO_KICKED_ENEMY_LISTENER_H

#include "../EventEngine/Event.hpp"
#include "../EventEngine/EventListener.hpp"
#include "../../Sound/SoundEngine.hpp"
#include <string>

/**
* @author Kevin Guillaumond <kevin.guillaumond@gmail.com>
*/
class MarioKickedEnemyListener : public EventListener
{
	public:
		MarioKickedEnemyListener(SoundEngine* _soundEngine);

		/**
		* Called when an mario_kicks_enemy event is dispatched
		* @param string eventType Type of received event
		* @param Event* event
		*/
		void onEvent(const std::string &_eventType, Event* _event);

	private:
		SoundEngine* m_soundEngine;
};

#endif // MARIO_KICKED_ENEMY_LISTENER_H
