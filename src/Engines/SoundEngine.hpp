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
        SoundEngine(EventEngine*);
        ~SoundEngine();

        void Frame();

		void StartLevelMusic(std::string _lvlName);
		void PlaySound(SoundType _type);

    private:
		virtual void CreateListeners();

		std::map<SoundType, sf::SoundBuffer> m_soundBuffers;
		sf::Sound *m_soundBeingPlayed;
		bool m_deathSoundIsPlaying; // This sound is particular because it stops the music and no input is possible while it's playing

		std::vector<std::string> m_musicNames;
		sf::Music *m_currentMusic;
		int m_indexCurrentMusic;

		void ProcessEvent(EngineEvent& _event);

		void LoadSounds();
		void LoadSoundFromFile(SoundType _type, std::string _name);

		void StoreMusicNames();
		void ChangeMusic();
		void PlayMusic(std::string _musicName);

		static const std::string soundsPath;
};

#endif // SOUNDENGINE_H
