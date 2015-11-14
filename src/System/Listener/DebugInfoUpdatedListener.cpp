#include "DebugInfoUpdatedListener.hpp"
#include <iostream>

DebugInfoUpdatedListener::DebugInfoUpdatedListener(GraphicsEngine* _graphicsEngine)
{
	m_graphicsEngine = _graphicsEngine;
}

void DebugInfoUpdatedListener::onEvent(const std::string &_eventType, Event* _event)
{
	m_graphicsEngine->StoreDebugInfo(_event->GetDebugInfo());
}
