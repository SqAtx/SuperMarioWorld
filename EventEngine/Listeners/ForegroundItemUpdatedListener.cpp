#include "../../System/Listener/ForegroundItemUpdatedListener.hpp"
#include <iostream>

ForegroundItemUpdatedListener::ForegroundItemUpdatedListener(GameEngine* _gameEngine)
{
	m_gameEngine = _gameEngine;
	m_graphicsEngine = NULL;
}

ForegroundItemUpdatedListener::ForegroundItemUpdatedListener(GraphicsEngine* _graphicsEngine)
{
	m_gameEngine = NULL;
	m_graphicsEngine = _graphicsEngine;
}

void ForegroundItemUpdatedListener::onEvent(const std::string &_eventType, Event* _event)
{
	if (m_gameEngine != NULL && _event->GetID() != 0)
		m_gameEngine->UpdateForegroundItem(_event->GetID(), _event->GetCoordinates());
	if (m_graphicsEngine != NULL && _event->GetInfoForDisplay() != NULL)
		m_graphicsEngine->UpdateForegroundItem(_event->GetInfoForDisplay());
}
