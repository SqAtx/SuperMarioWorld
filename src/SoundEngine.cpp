#include "SoundEngine.hpp"

SoundEngine::SoundEngine(Game *_g): Engine (_g)
{
    //ctor
}

SoundEngine::~SoundEngine()
{
    //dtor
}

void SoundEngine::Frame()
{
	ProcessQueue();
}

void SoundEngine::ProcessEvent(EngineEvent& _event)
{
	switch (_event.m_type)
	{

	default:
		break;
	}
}