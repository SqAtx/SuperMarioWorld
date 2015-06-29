#ifndef GAME_H
#define GAME_H

#include <mutex>

#include "Engines/GameEngine.hpp"
#include "Engines/GraphicsEngine.hpp"
#include "Engines/SoundEngine.hpp"

/*
    Base class of the game
    Contains the entry point of the game and the creation of the engines
*/
class Game
{
    public:
        Game ();
        ~Game();

        void Run();
        void Stop();

    private:
        bool m_running;
        std::mutex m_running_mutex;

        GameEngine *m_g;
        GraphicsEngine *m_gfx;
        SoundEngine *m_s;
};

#endif // GAME_H
