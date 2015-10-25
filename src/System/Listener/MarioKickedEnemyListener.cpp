#include "MarioKickedEnemyListener.hpp"
#include <iostream>

MarioKickedEnemyListener::MarioKickedEnemyListener(SoundEngine* _soundEngine)
{
	m_soundEngine = _soundEngine;
}

void MarioKickedEnemyListener::onEvent(const std::string &_eventType, Event* _event)
{
	m_soundEngine->PlaySound(KICK_SND);
}
