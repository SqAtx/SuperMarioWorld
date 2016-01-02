#include "NewCharacterReadListener.hpp"
#include <iostream>

NewCharacterReadListener::NewCharacterReadListener(GameEngine* _gameEngine)
{
	m_gameEngine = _gameEngine;
}

void NewCharacterReadListener::onEvent(const std::string &_eventType, Event* _event)
{
	MovingObject *character = _event->GetMovingObject();
	if (character->GetName() == "Mario")
		m_gameEngine->SetMarioInitialPosition(character->GetPosition());

	m_gameEngine->AddCharacterToArray(character);
	m_gameEngine->AddForegroundItemToArray(character);
}
