#include "../../System/Listener/NewForegroundItemReadListener.hpp"
#include <iostream>

NewForegroundItemReadListener::NewForegroundItemReadListener(GameEngine* _gameEngine)
{
	m_gameEngine = _gameEngine;
	m_graphicsEngine = NULL;
}

NewForegroundItemReadListener::NewForegroundItemReadListener(GraphicsEngine* _graphicsEngine)
{
	m_gameEngine = NULL;
	m_graphicsEngine = _graphicsEngine;
}

void NewForegroundItemReadListener::onEvent(const std::string &_eventType, Event* _event)
{
	if (m_gameEngine != NULL)
		m_gameEngine->AddForegroundItemToArray(_event->GetDisplayableObject());
	if (m_graphicsEngine != NULL)
		m_graphicsEngine->UpdateForegroundItem(&(_event->GetDisplayableObject()->GetInfoForDisplay()));
}
