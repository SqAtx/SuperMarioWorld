#include "ForegroundItemRemovedListener.hpp"
#include <iostream>

ForegroundItemRemovedListener::ForegroundItemRemovedListener(GraphicsEngine* _graphicsEngine)
{
	m_graphicsEngine = _graphicsEngine;
}

void ForegroundItemRemovedListener::onEvent(const std::string &_eventType, Event* _event)
{
	m_graphicsEngine->DeleteForegroundItem(_event->GetID());
}
