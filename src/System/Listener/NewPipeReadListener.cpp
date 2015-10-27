#include "NewPipeReadListener.hpp"
#include <iostream>

NewPipeReadListener::NewPipeReadListener(GameEngine* _gameEngine)
{
	m_gameEngine = _gameEngine;
}

void NewPipeReadListener::onEvent(const std::string &_eventType, Event* _event)
{
	m_gameEngine->AddPipeToArray(_event->GetPipe());
	m_gameEngine->AddForegroundItemToArray(_event->GetPipe());
}
