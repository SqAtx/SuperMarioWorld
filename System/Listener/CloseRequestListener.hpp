#ifndef CLOSE_REQUEST_LISTENER_H
#define CLOSE_REQUEST_LISTENER_H

#include "../../EventEngine/Event.hpp"
#include "../../EventEngine/EventListener.hpp"
#include "../../Game.hpp"
#include <string>

/**
 * @author Nicolas Djambazian <nicolas@djambazian.fr>
 */
class CloseRequestListener : public EventListener
{
    public:

        CloseRequestListener(Game* _game);

        /**
         * Called when an CloseRequestEvent is dispatched
         * @param string eventType Type of received event
         * @param Event* event
         */
         void onEvent(const std::string &_eventType, Event* _event);

     private:

         Game* m_game;
};

#endif // CLOSE_REQUEST_LISTENER_H
