#include "LevelStartListener.hpp"

LevelStartListener::LevelStartListener(SoundEngine* _soundEngine)
{
	m_soundEngine = _soundEngine;
}

void LevelStartListener::onEvent(const std::string &_eventType, Event* _event)
{
	m_soundEngine->StartLevelMusic(_event->GetString());
}
