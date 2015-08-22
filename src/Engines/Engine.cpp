#include "Engine.hpp"

Engine::Engine (EventEngine* _eventEngine)
{
    m_eventEngine = _eventEngine;
}

Engine::~Engine()
{

}

// Attach a new engine
void Engine::Attach_Engine (std::string _name, Engine* _engine)
{
    m_engines[_name] = _engine;
}

void Engine::PushEvent(EngineEvent& _event)
{
	m_eventsQueue.push(_event);
}

void Engine::ProcessQueue()
{
	while (! m_eventsQueue.empty())
	{
		EngineEvent event = m_eventsQueue.front();
		m_eventsQueue.pop();

		ProcessEvent(event);
	}
}
