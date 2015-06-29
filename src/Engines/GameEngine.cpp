#include "GameEngine.hpp"
#include "../Game.hpp"

GameEngine::GameEngine(Game *_g) : Engine(_g), m_levelStarted(false), m_indexMario(-1)
{

}

GameEngine::~GameEngine()
{
	for (int i = 0; i < m_characters.size(); i++)
		delete m_characters[i];
	for (int i = 0; i < m_listForegroundItems.size(); i++)
		delete m_listForegroundItems[i];
}

void GameEngine::Frame()
{
	assert(false); // The overloaded Frame function should be called instead
}

void GameEngine::Frame(float _dt)
{
	if (!m_levelStarted)
		StartLevel("testlvl"); // In the future there will be some sort of level selection so this call will be moved

	ProcessQueue();

	for (int i = 0; i < m_characters.size(); i++)
	{
		if (m_characters[i] != NULL)
		{
			if (1 / _dt > 20) // No updating at all if framerate < 20 (usually the first few iterations) because it results in inacurrate updating (like Mario drops 300 pixels at beginning of level)
				UpdateCharacterPosition(*m_characters[i], _dt);

			HandleCollisionsWithLevel(*m_characters[i]);
			HandleCollisionsWithMapEdges(*m_characters[i]);
			CheckCharacterDeath(*m_characters[i]);
			SendCharacterPosition(i);
		}
	}
}

void GameEngine::ProcessEvent(EngineEvent& _event)
{
	switch (_event.m_type)
	{
		case KEY_PRESSED:
			HandlePressedKey(_event.data.m_key);
			break;
		case KEY_RELEASED:
			HandleReleasedKey(_event.data.m_key);
			break;
		case INFO_POS_LVL:
		{
			auto DOtoUpdate = m_listForegroundItems.find(_event.data.m_id);
			if (DOtoUpdate != m_listForegroundItems.end() && DOtoUpdate->second != NULL)
				m_listForegroundItems[_event.data.m_id]->SetCoordinates(_event.m_rect);
			break;
		}
		case DEATH_SOUND_STARTED:
			m_deathSoundIsPlaying = true;
			break;
		case DEATH_SOUND_STOPPED:
			m_deathSoundIsPlaying = false;
			break;
		case GAME_STOPPED:
			m_parent->Stop();
			break;
		default:
			break;
	}
}

void GameEngine::HandlePressedKey(sf::Keyboard::Key _key)
{
	Player *mario = m_indexMario != -1 ? (Player*)m_characters[m_indexMario] : NULL; // Clarity

	switch (_key)
	{
		case sf::Keyboard::Left:
			if (mario != NULL)
				mario->Move(GO_LEFT);
			break;
		case sf::Keyboard::Right:
			if (mario != NULL)
				mario->Move(GO_RIGHT);
			break;
		case sf::Keyboard::C:
			if (mario != NULL)
				mario->ToggleRun(true);
			break;
		case sf::Keyboard::Space:
			if (mario != NULL && mario->Jump())
			{
				EngineEvent playJumpSound(PLAY_SOUND, JUMP_SND);
				m_engines["s"]->PushEvent(playJumpSound);
			}
			break;
		case sf::Keyboard::Escape:
			if (m_indexMario == -1 && CanRespawnMario())
			{
				Player *mario = new Player("mario", m_initPosMario);
				m_indexMario = AddCharacterToArray(mario);
				m_listForegroundItems[mario->GetID()] = mario;

				EngineEvent playMusic(LEVEL_START);
				m_engines["s"]->PushEvent(playMusic);
			}
			break;
		default:
			break;
	}
}

bool GameEngine::CanRespawnMario()
{
	return !m_deathSoundIsPlaying;
}

void GameEngine::HandleReleasedKey(sf::Keyboard::Key _key)
{
	Player *mario = m_indexMario != -1 ? (Player*)m_characters[m_indexMario] : NULL; // Clarity

	switch (_key)
	{
		case sf::Keyboard::Left:
			if (mario != NULL)
				mario->Move(STOP_LEFT);
			break;
		case sf::Keyboard::Right:
			if (mario != NULL)
				mario->Move(STOP_RIGHT);
			break;
		case sf::Keyboard::C:
			if (mario != NULL)
				mario->ToggleRun(false);
			break;
		case sf::Keyboard::Space:
			if (mario != NULL)
				mario->EndJump();
			break;
		default:
			break;
	}
}

void GameEngine::StartLevel(std::string _lvlName)
{
	LoadLevel(_lvlName);

	EngineEvent startLevel(LEVEL_START);
	m_engines["s"]->PushEvent(startLevel);

	m_levelStarted = true;
}

/* Takes the place of the first NULL pointer (= dead character), or is pushed at the end */
int GameEngine::AddCharacterToArray(MovingObject *_character)
{
	int initialSize = m_characters.size();
	for (int i = 0; i < initialSize; i++)
	{
		if (m_characters[i] == NULL)
		{
			m_characters[i] = _character;
			return i;
		}
	}
	m_characters.push_back(_character);
	return initialSize;
}

void GameEngine::UpdateCharacterPosition(MovingObject& _character, float _dt)
{
	unsigned int id = _character.GetID();

	_character.UpdatePosition(_dt);

	sf::Vector2f pos = _character.GetPosition();
	m_listForegroundItems[id]->SetX(pos.x);
	m_listForegroundItems[id]->SetY(pos.y);
}

void GameEngine::CheckCharacterDeath(MovingObject& _character)
{
	if (_character.IsDead())
		KillCharacter(_character);
}

void GameEngine::KillCharacter(MovingObject& _character)
{
	for (int i = 0; i < m_characters.size(); i++)
	{
		if (m_characters[i] != NULL && m_characters[i]->GetID() == _character.GetID())
		{
			m_listForegroundItems.erase(m_characters[i]->GetID());

			delete m_characters[i];
			m_characters[i] = NULL;

			if (i == m_indexMario)
			{
				m_indexMario = -1;

				EngineEvent deathSound(PLAY_SOUND, DEATH_SND);
				m_engines["s"]->PushEvent(deathSound);
			}

			std::cout << "Character #" << i << " died" << std::endl;
		}
	}
}

// Send Mario's position to gfx
void GameEngine::SendCharacterPosition(int _indexCharacter)
{
	MovingObject *character = m_characters[_indexCharacter];
	if (character == NULL)
		return;

	EngineEvent posInfo(INFO_POS_CHAR, character->GetInfoForDisplay());
	m_engines["gfx"]->PushEvent(posInfo);
#ifdef DEBUG_MODE
	if (_indexCharacter == m_indexMario)
	{
		EngineEvent debugInfo(INFO_DEBUG, character->GetDebugInfo());
		m_engines["gfx"]->PushEvent(debugInfo);
	}
#endif
}
