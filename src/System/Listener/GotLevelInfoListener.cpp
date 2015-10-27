#include "GotLevelInfoListener.hpp"
#include <iostream>

GotLevelInfoListener::GotLevelInfoListener(GameEngine* _gameEngine)
{
	m_gameEngine = _gameEngine;
	m_graphicsEngine = NULL;
}

GotLevelInfoListener::GotLevelInfoListener(GraphicsEngine* _graphicsEngine)
{
	m_gameEngine = NULL;
	m_graphicsEngine = _graphicsEngine;
}

void GotLevelInfoListener::onEvent(const std::string &_eventType, Event* _event)
{
	if (m_gameEngine != NULL)
		m_gameEngine->StoreLevelInfo(*(_event->GetLevelInfo()));
	if (m_graphicsEngine != NULL)
		m_graphicsEngine->RceiveLevelInfo(*(_event->GetLevelInfo()));
}
