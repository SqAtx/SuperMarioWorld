#ifndef CHARACTER_DIED_LISTENER_H
#define CHARACTER_DIED_LISTENER_H

#include "../EventEngine/Event.hpp"
#include "../EventEngine/EventListener.hpp"
#include "../../Game/GameEngine.hpp"
#include "../../Graphics/GraphicsEngine.hpp"
#include "../../Sound/SoundEngine.hpp"
#include <string>

/**
* @author Kevin Guillaumond <kevin.guillaumond@gmail.com>
*/
class CharacterDiedListener : public EventListener
{
	public:
		CharacterDiedListener(GameEngine* _gameEngine);
		CharacterDiedListener(GraphicsEngine* _graphicsEngine);
		CharacterDiedListener(SoundEngine* _soundEngine);

		/**
		* Called when an character_died event is dispatched
		* @param string eventType Type of received event
		* @param Event* event
		*/
		void onEvent(const std::string &_eventType, Event* _event);

	private:
		GameEngine* m_gameEngine;
		GraphicsEngine* m_graphicsEngine;
		SoundEngine* m_soundEngine;
};

#endif // CHARACTER_DIED_LISTENER_H
