#ifndef SOUNDENGINE_H
#define SOUNDENGINE_H

#include "Engine.hpp"
#include <SFML/Audio.hpp>

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
		std::map<SoundType, sf::SoundBuffer> m_soundBuffers;
		sf::Sound *m_soundBeingPlayed;

		void ProcessEvent(EngineEvent& _event);
		void LoadSounds();
		void LoadSoundFromFile(SoundType _type, std::string _name);
		void PlaySound(SoundType _type);

		static const std::string soundsPath;
};

#endif // SOUNDENGINE_H
