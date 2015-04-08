#ifndef SOUNDENGINE_H
#define SOUNDENGINE_H

#include "Engine.hpp"

/*
    Sound engine: handles the sound effects and the music
*/
class SoundEngine : public Engine
{
    public:
        SoundEngine(Game *_g);
        ~SoundEngine();

        void Frame();

    private:
		void ProcessEvent(EngineEvent& _event);
};

#endif // SOUNDENGINE_H
