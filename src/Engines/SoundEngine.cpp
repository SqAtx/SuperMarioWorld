#include "SoundEngine.hpp"
#include "../System/Listener/MarioJumpListener.hpp"
#include "../System/Listener/LevelStartListener.hpp"

const std::string SoundEngine::soundsPath = "../assets/sounds/";

SoundEngine::SoundEngine(EventEngine* _eventEngine) : Engine(_eventEngine), m_indexCurrentMusic(-1)
{
	m_soundBeingPlayed = new sf::Sound();
	m_currentMusic = new sf::Music();
	LoadSounds();
	StoreMusicNames();

	CreateListeners();
}

void SoundEngine::CreateListeners()
{
	LevelStartListener* levelStartListener = new LevelStartListener(this);
	m_eventEngine->addListener("game.level_start", levelStartListener);
	m_createdListeners.push_back(levelStartListener);

	MarioJumpListener* marioJumpListener = new MarioJumpListener(this);
	m_eventEngine->addListener("game.mario_jump", marioJumpListener);
	m_createdListeners.push_back(marioJumpListener);
}

SoundEngine::~SoundEngine()
{
	delete m_soundBeingPlayed;
	delete m_currentMusic;

	for (unsigned int i = 0; i < m_createdListeners.size(); i++)
		delete m_createdListeners[i];
}

void SoundEngine::Frame()
{
	if (m_deathSoundIsPlaying && m_soundBeingPlayed->getStatus() != sf::SoundSource::Status::Playing)
	{
		m_deathSoundIsPlaying = false;
		EngineEvent deathSoundStopped(DEATH_SOUND_STOPPED);
		m_engines["g"]->PushEvent(deathSoundStopped);
	}

	if (m_indexCurrentMusic != -1 && m_currentMusic->getStatus() == sf::SoundSource::Status::Stopped)
		ChangeMusic();

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
	LoadSoundFromFile(KICK_SND, "Kick_Sound_Effect.ogg");
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
	// Music stops when Mario dies
	if (_type == DEATH_SND)
	{
		m_currentMusic->stop();
		m_indexCurrentMusic = -1;

		m_deathSoundIsPlaying = true;
		EngineEvent deathSoundStarted(DEATH_SOUND_STARTED);
		m_engines["g"]->PushEvent(deathSoundStarted);
	}

	m_soundBeingPlayed->setBuffer(m_soundBuffers[_type]); // Could optimize this by remembering the last buffer set
	m_soundBeingPlayed->play();
}

void SoundEngine::StoreMusicNames()
{
	m_musicNames.push_back("Super_Jungle_Brothers_OC_ReMix.ogg");
	m_musicNames.push_back("SwankyVegas_OC_ReMix.ogg");
}

void SoundEngine::StartLevelMusic(std::string _lvlName) // Beginning of level
{
	PlayMusic(m_musicNames[0]);
	m_indexCurrentMusic = 0;
}

void SoundEngine::ChangeMusic()
{
	m_indexCurrentMusic = (m_indexCurrentMusic == (int) m_musicNames.size() - 1) ? 0 : m_indexCurrentMusic + 1;
	PlayMusic(m_musicNames[m_indexCurrentMusic]);
}

void SoundEngine::PlayMusic(std::string _musicName)
{
	std::string musicFullName = SoundEngine::soundsPath + _musicName;
	if (!m_currentMusic->openFromFile(musicFullName))
		std::cerr << "Can't open music file " << musicFullName << std::endl;
	else
		m_currentMusic->play();
}
