#include "ForegroundItemUpdatedListener.hpp"
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
	if (m_gameEngine != NULL)
		;// m_gameEngine->StoreLevelInfo(_event->GetLevelInfo());
	if (m_graphicsEngine != NULL)
		m_graphicsEngine->UpdateForegroundItem(_event->GetInfoForDisplay());
}
