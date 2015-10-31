#include "CharacterDiedListener.hpp"
#include <iostream>

CharacterDiedListener::CharacterDiedListener(GraphicsEngine* _graphicsEngine)
{
	m_graphicsEngine = _graphicsEngine;
	m_soundEngine = NULL;
}

CharacterDiedListener::CharacterDiedListener(SoundEngine* _soundEngine)
{
	m_graphicsEngine = NULL;
	m_soundEngine = _soundEngine;
}

void CharacterDiedListener::onEvent(const std::string &_eventType, Event* _event)
{
	if (m_graphicsEngine != NULL)
		m_graphicsEngine->RemoveDisplayableObject(_event->GetInfoForDisplay()->id);
	if (m_soundEngine != NULL && _event->GetInfoForDisplay()->name == "mario")
		m_soundEngine->PlaySound(DEATH_SND);
}
