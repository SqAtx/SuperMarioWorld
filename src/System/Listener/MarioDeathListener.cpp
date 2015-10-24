#include "MarioDeathListener.hpp"
#include <iostream>

MarioDeathListener::MarioDeathListener(SoundEngine* _soundEngine)
{
	m_soundEngine = _soundEngine;
}

void MarioDeathListener::onEvent(const std::string &_eventType, Event* _event)
{
	m_soundEngine->PlaySound(DEATH_SND);
}
