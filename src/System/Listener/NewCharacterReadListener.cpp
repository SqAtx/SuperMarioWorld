#include "NewCharacterReadListener.hpp"
#include <iostream>

NewCharacterReadListener::NewCharacterReadListener(GameEngine* _gameEngine)
{
	m_gameEngine = _gameEngine;
}

void NewCharacterReadListener::onEvent(const std::string &_eventType, Event* _event)
{
	m_gameEngine->AddCharacterToArray(_event->GetMovingObject());
	m_gameEngine->AddForegroundItemToArray(_event->GetMovingObject());
}
