#include "../../System/Listener/KeyboardListener.hpp"
#include <iostream>

KeyboardListener::KeyboardListener(GameEngine* _gameEngine)
{
	m_gameEngine = _gameEngine;
}

void KeyboardListener::onEvent(const std::string &_eventType, Event* _event)
{
	KeyboardEvent* keyEvent = (KeyboardEvent*)_event;
	if (keyEvent->GetType() == sf::Event::KeyPressed)
		m_gameEngine->HandlePressedKey(keyEvent->GetKey());
	else if (keyEvent->GetType() == sf::Event::KeyReleased)
		m_gameEngine->HandleReleasedKey(keyEvent->GetKey());
}
