#include "../System/EventEngine/EventEngine.hpp"

void EventEngine::addListener(EventListener* _listener)
{
    m_generalsListeners.push_back(_listener);
}

void EventEngine::addListener(const std::string &_eventName, EventListener* _listener)
{
    if (m_specificListeners.count(_eventName) == 0) 
	{
        std::vector<EventListener*> vector;
        m_specificListeners[_eventName] = vector;
    }
    m_specificListeners[_eventName].push_back(_listener);
}

void EventEngine::dispatch(const std::string &_eventName, Event* _event)
{
    // If some performance issue, we can think about sending the event in a new thread
    if (m_specificListeners.count(_eventName) != 0) 
	{
        for (unsigned int i = 0; i < m_specificListeners[_eventName].size(); i++) 
		{
            m_specificListeners[_eventName][i]->onEvent(_eventName, _event);
        }
    }

    for (unsigned int i = 0; i < m_generalsListeners.size(); i++) {
        m_generalsListeners[i]->onEvent(_eventName, _event);
    }
}
