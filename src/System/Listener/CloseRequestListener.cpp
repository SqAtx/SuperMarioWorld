#include "CloseRequestListener.hpp"
#include <iostream>

CloseRequestListener::CloseRequestListener(Game* _game)
{
    m_game = _game;
}

 void CloseRequestListener::onEvent(const std::string &_eventType, Event* _event)
 {
     m_game->Stop();
 }
