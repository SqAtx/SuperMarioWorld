#include "MarioJumpListener.hpp"
#include <iostream>

MarioJumpListener::MarioJumpListener(SoundEngine* _soundEngine)
{
	m__soundEngine = _soundEngine;
}

void MarioJumpListener::onEvent(const std::string &_eventType, Event* _event)
{
	m__soundEngine->PlaySound(JUMP_SND);
}
