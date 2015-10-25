#include "GameEngine.hpp"
#include "../Game.hpp"
#include "../System/Listener/KeyboardListener.hpp"
#include "../Game/GameEvents.hpp"

GameEngine::GameEngine(EventEngine *_eventEngine) : Engine(_eventEngine), m_levelStarted(false), m_indexMario(-1)
{
	m_collisionHandler = new CollisionHandler(this);
	m_levelImporter = new LevelImporter(this);

	KeyboardListener* keyboardListener = new KeyboardListener(this);
	m_eventEngine->addListener("graphics.key_event", keyboardListener);
	m_createdListeners.push_back(keyboardListener);
}

GameEngine::~GameEngine()
{
	delete m_collisionHandler;
	delete m_levelImporter;

	for (unsigned int i = 0; i < m_characters.size(); i++)
		delete m_characters[i];
	for (unsigned int i = 0; i < m_listForegroundItems.size(); i++)
		delete m_listForegroundItems[i];

	for (unsigned int i = 0; i < m_createdListeners.size(); i++)
		delete m_createdListeners[i];
}

void GameEngine::Frame()
{
	assert(false); // The overloaded Frame function should be called instead
}

void GameEngine::Frame(float _dt)
{
	MovingObject *currentCharacter = NULL;

	if (!m_levelStarted)
		StartLevel("biglvl"); // In the future there will be some sort of level selection so this call will be moved

	ProcessQueue();

	// Spawn enemies from pipes
	for (std::map<unsigned int, Pipe*>::iterator it = m_listPipes.begin(); it != m_listPipes.end(); ++it)
	{
		if (it->second->GetPipeType() == SPAWN)
			it->second->HandleSpawnEnemies(_dt);
	}

	for (unsigned int i = 0; i < m_characters.size(); i++)
	{
		currentCharacter = m_characters[i];
		if (currentCharacter != NULL)
		{
			if (1 / _dt > 20) // No updating at all if framerate < 20 (usually the first few iterations) because it results in inacurrate updating (like Mario drops 300 pixels at beginning of level)
				UpdateCharacterPosition(*currentCharacter, _dt);

			HandleCollisions(*currentCharacter);

			CheckCharacterDeath(*currentCharacter);
			SendCharacterPosition(i);
		}
	}
}

void GameEngine::ProcessEvent(EngineEvent& _event)
{
	switch (_event.m_type)
	{
		case INFO_LVL:
			m_collisionHandler->SetLevelSize(_event.m_levelInfo.size);
			break;
		case INFO_POS_LVL:
		{
			auto DOtoUpdate = m_listForegroundItems.find(_event.data.m_id);
			if (DOtoUpdate != m_listForegroundItems.end() && DOtoUpdate->second != NULL)
				m_listForegroundItems[_event.data.m_id]->SetCoordinates(_event.m_rect);
			break;
		}
		case NEW_FOREGROUND_ITEM:
			AddForegroundItemToArray(_event.m_displayable);
			break;
		case NEW_CHARACTER:
			AddCharacterToArray(_event.m_moving);
			AddForegroundItemToArray(_event.m_moving);
			break;
		case NEW_PIPE:
			AddPipeToArray(_event.m_pipe);
			AddForegroundItemToArray(_event.m_pipe);
			break;
		case DEATH_SOUND_STARTED:
			m_deathSoundIsPlaying = true;
			break;
		case DEATH_SOUND_STOPPED:
			m_deathSoundIsPlaying = false;
			break;
		default:
			break;
	}
}

void GameEngine::HandlePressedKey(sf::Keyboard::Key _key)
{
	Event tmpEvent;
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
				m_eventEngine->dispatch(MARIO_JUMP, &tmpEvent);
			}
			break;
		case sf::Keyboard::Escape:
			if (m_indexMario == -1 && CanRespawnMario())
			{
				Player *mario = new Player("mario", m_initPosMario);
				AddCharacterToArray(mario);
				m_listForegroundItems[mario->GetID()] = mario;

				tmpEvent.SetString(m_currentLevelName);
				m_eventEngine->dispatch(LEVEL_START, &tmpEvent);
			}
			break;
		case sf::Keyboard::N:
			m_listPipes[1]->ToggleSpawn();
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
	m_levelImporter->LoadLevel(_lvlName);
	m_currentLevelName = _lvlName;

	Event startLevel(_lvlName);
	m_eventEngine->dispatch(LEVEL_START, &startLevel);

	m_levelStarted = true;
}

/* Takes the place of the first NULL pointer (= dead character), or is pushed at the end */
void GameEngine::AddCharacterToArray(MovingObject *_character)
{
	int initialSize = m_characters.size();
	int indexCharacter = -1;
	for (int i = 0; i < initialSize; i++)
	{
		if (m_characters[i] == NULL)
		{
			m_characters[i] = _character; // Character takes the spot of a dead character
			indexCharacter = i;
			break;
		}
	}

	if (indexCharacter == -1)
	{
		m_characters.push_back(_character);
		indexCharacter = initialSize;
	}

	if (_character->GetName() == "mario")
		m_indexMario = indexCharacter;
}

void GameEngine::AddForegroundItemToArray(DisplayableObject *_item)
{
	m_listForegroundItems[_item->GetID()] = _item;
}

void GameEngine::AddPipeToArray(Pipe *_pipe)
{
	m_listPipes[_pipe->GetPipeId()] = _pipe;
};


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
	for (unsigned int i = 0; i < m_characters.size(); i++)
	{
		if (m_characters[i] != NULL && m_characters[i]->GetID() == _character.GetID())
		{
			m_listForegroundItems.erase(m_characters[i]->GetID());

			delete m_characters[i];
			m_characters[i] = NULL;

			if ((int) i == m_indexMario)
			{
				m_indexMario = -1;

				Event death;
				m_eventEngine->dispatch(MARIO_DEATH, &death);
			}
		}
	}
}

// Send character's position to gfx
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

//	Handles collisions between the object and all the DisplayableObjects in m_listForegroundItems and with the map edges: detection and reaction.
void GameEngine::HandleCollisions(MovingObject& _obj)
{
	if (m_listForegroundItems.size() <= 1)
		return;

	CollisionDirection tmpDirection = NO_COL;

	if (_obj.CanCollide())
	{
		// What happens if there is a collision so _obj is moved and there is another one and _obj is moved again ? The first collision would need to be handled again
		for (std::map<unsigned int, DisplayableObject*>::iterator it = m_listForegroundItems.begin(); it != m_listForegroundItems.end(); ++it)
		{
			tmpDirection = m_collisionHandler->DetectCollisionWithObj(_obj, *(it->second));

			if (tmpDirection != NO_COL)
			{
				m_collisionHandler->ReactToCollisionsWithObj(_obj, *(m_listForegroundItems[it->first]), tmpDirection);

				if (it->second->GetClass() == ENEMY && ((MovingObject*)it->second)->HasBeenHit()) // If class is ENEMY then it's a MovingObject
				{
					Event event;
					m_eventEngine->dispatch(MARIO_KICKED_ENEMY, &event);
				}
			}
		}
	}

	m_collisionHandler->HandleCollisionsWithMapEdges(_obj);
}
