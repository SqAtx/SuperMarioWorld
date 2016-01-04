#include "../../System/Listener/ToggleIgnoreInputListener.hpp"
#include <iostream>

ToggleIgnoreInputListener::ToggleIgnoreInputListener(GameEngine* _gameEngine)
{
	m_gameEngine = _gameEngine;
}

void ToggleIgnoreInputListener::onEvent(const std::string &_eventType, Event* _event)
{
	m_gameEngine->ToggleIgnoreUserInput(_event->GetBool());
}
