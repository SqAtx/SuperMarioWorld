#include "NewForegroundItemReadListener.hpp"
#include <iostream>

NewForegroundItemReadListener::NewForegroundItemReadListener(GameEngine* _gameEngine)
{
	m_gameEngine = _gameEngine;
}

void NewForegroundItemReadListener::onEvent(const std::string &_eventType, Event* _event)
{
	m_gameEngine->AddForegroundItemToArray(_event->GetDisplayableObject());
}
