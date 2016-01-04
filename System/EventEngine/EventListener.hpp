#ifndef EVENT_LISTENER_H
#define EVENT_LISTENER_H

#include "Event.hpp"
#include <string>

/**
 * Base class for event listeners
 * @author Nicolas Djambazian <nicolas@djambazian.fr>
 */
class EventListener
{
    public:

        virtual ~EventListener(){};

        /**
         * Called when an event is dispached
         * @param string eventType Type of received event
         * @param Event* event
         */
        virtual void onEvent(const std::string &_eventType, Event* _event) = 0;
};

#endif // EVENT_LISTENER_H
