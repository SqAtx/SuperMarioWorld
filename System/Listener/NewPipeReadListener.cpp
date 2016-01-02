#include "NewPipeReadListener.hpp"
#include <iostream>

NewPipeReadListener::NewPipeReadListener(GameEngine* _gameEngine)
{
	m_gameEngine = _gameEngine;
	m_graphicsEngine = NULL;
}

NewPipeReadListener::NewPipeReadListener(GraphicsEngine* _graphicsEngine)
{
	m_gameEngine = NULL;
	m_graphicsEngine = _graphicsEngine;
}

void NewPipeReadListener::onEvent(const std::string &_eventType, Event* _event)
{
	if (m_gameEngine != NULL)
	{
		m_gameEngine->AddPipeToArray(_event->GetPipe());
		m_gameEngine->AddForegroundItemToArray(_event->GetPipe());
	}
	if (m_graphicsEngine != NULL)
		m_graphicsEngine->UpdateForegroundItem(&(_event->GetPipe()->GetInfoForDisplay()));
}
