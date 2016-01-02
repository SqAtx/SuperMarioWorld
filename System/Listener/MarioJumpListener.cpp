#include "MarioJumpListener.hpp"
#include <iostream>

MarioJumpListener::MarioJumpListener(SoundEngine* _soundEngine)
{
	m_soundEngine = _soundEngine;
}

void MarioJumpListener::onEvent(const std::string &_eventType, Event* _event)
{
	m_soundEngine->PlaySound(JUMP_SND);
}
