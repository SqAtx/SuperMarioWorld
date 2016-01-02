#include "CharacterPositionUpdateListener.hpp"
#include <iostream>

CharacterPositionUpdateListener::CharacterPositionUpdateListener(GraphicsEngine* _graphicsEngine)
{
	m_graphicsEngine = _graphicsEngine;
}

void CharacterPositionUpdateListener::onEvent(const std::string &_eventType, Event* _event)
{
	m_graphicsEngine->ReceiveCharacterPosition(_event->GetInfoForDisplay());
}
