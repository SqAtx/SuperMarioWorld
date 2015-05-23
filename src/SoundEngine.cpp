#include "SoundEngine.hpp"

const std::string SoundEngine::soundsPath = "../assets/sounds/";

SoundEngine::SoundEngine(Game *_g): Engine (_g)
{
	m_soundBeingPlayed = new sf::Sound();
	LoadSounds();
}

SoundEngine::~SoundEngine()
{
	delete m_soundBeingPlayed;
}

void SoundEngine::Frame()
{
	ProcessQueue();
}

void SoundEngine::ProcessEvent(EngineEvent& _event)
{
	switch (_event.m_type)
	{
		case PLAY_SOUND:
			PlaySound(_event.data.m_sound);
			break;
		default:
			break;
	}
}

void SoundEngine::LoadSounds()
{
	LoadSoundFromFile(JUMP_SND, "Jump_Sound_Effect.ogg");
	LoadSoundFromFile(COIN_SND, "Coin_Sound_Effect.ogg");
	LoadSoundFromFile(DEATH_SND, "Mario_Death_Sound_Effect.ogg");
}

void SoundEngine::LoadSoundFromFile(SoundType _type, std::string _fileName)
{
	sf::SoundBuffer buffer;
	std::string soundFullName = SoundEngine::soundsPath + _fileName;
	if (!buffer.loadFromFile(soundFullName))
		std::cerr << "Can't load sound " << soundFullName << std::endl;
	else
		m_soundBuffers[_type] = buffer;
}

void SoundEngine::PlaySound(SoundType _type)
{
	std::cout << "Playing sound " << _type << std::endl;
	m_soundBeingPlayed->setBuffer(m_soundBuffers[_type]); // Could optimize this by remembering the last buffer set
	m_soundBeingPlayed->play();

	//while (sound.getStatus() == sf::Sound::Playing);
}