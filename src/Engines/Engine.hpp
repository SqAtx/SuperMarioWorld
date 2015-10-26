#ifndef ENGINE_H
#define ENGINE_H

#include <map>
#include <iostream>
#include <queue>

#include "EngineEvent.hpp"
#include "../EventEngine/EventEngine.hpp"

// Game needs Engine and Engine needs Game, we solve that problem with a forward declaration
class Game;

/*
    Abstract base class for all engines (game, graphics, sound, ...)
    Each engine has pointers to the Game parent and to the others engines
*/
class Engine
{
    public:
        Engine (EventEngine*);
		virtual ~Engine();

		void Attach_Engine (std::string _name, Engine* _engine);

		void PushEvent(EngineEvent& _event);
		void ProcessQueue();

        virtual void Frame() = 0;

    protected:
        EventEngine* m_eventEngine;
        std::map <std::string, Engine *> m_engines; // g for GameEngine, gfx for GraphicsEngine, s for SoundEngine

		std::queue<EngineEvent> m_eventsQueue; // A queue of events to deal with

		std::vector<EventListener*> m_createdListeners;

	private:
		virtual void ProcessEvent(EngineEvent& _event) = 0;
		virtual void CreateListeners() = 0;
};

#endif // ENGINE_H
