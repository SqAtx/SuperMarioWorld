#ifndef EVENT_ENGINE_H
#define EVENT_ENGINE_H

#include "Event.hpp"
#include "EventListener.hpp"
#include <map>
#include <iostream>
#include <queue>
#include <string>

/**
 * Handle Event sending
 * @author Nicolas Djambazian <nicolas@djambazian.fr>
 */
class EventEngine
{
    public:
        /**
         * Add an Event lister to the Engine
         * which will be called on every event
         * @param EventListener _listener
         */
        void addListener(EventListener* _listener);

        /**
         * Add an Event lister to the Engine
         * which will be called for one type of event only
         * @param string _eventNme Event to listen
         * @param EventListener* _listener
         */
        void addListener(const std::string &_eventName, EventListener* _listener);

        /**
         * send a new Event
         * @param string _eventType Name of the event
         * @param Event* _event The event object
         */
        void dispatch(const std::string &_eventType, Event* _event);

    private:
        std::map<std::string, std::vector<EventListener*>> m_specificListeners;
        std::vector<EventListener*> m_generalsListeners;
};

#endif // EVENT_ENGINE_H
