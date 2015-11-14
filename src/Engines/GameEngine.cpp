#include "GameEngine.hpp"
#include "../Game.hpp"
#include "../System/Listener/CharacterDiedListener.hpp"
#include "../System/Listener/ForegroundItemUpdatedListener.hpp"
#include "../System/Listener/GotLevelInfoListener.hpp"
#include "../System/Listener/KeyboardListener.hpp"
#include "../System/Listener/NewCharacterReadListener.hpp"
#include "../System/Listener/NewForegroundItemReadListener.hpp"
#include "../System/Listener/NewPipeReadListener.hpp"
#include "../Game/GameEvents.hpp"

GameEngine::GameEngine(EventEngine *_eventEngine) : Engine(_eventEngine), m_levelStarted(false), m_indexMario(-1)
{
	m_collisionHandler = new CollisionHandler(this, m_eventEngine);
	m_levelImporter = new LevelImporter(this, _eventEngine);
	CreateListeners();

#ifdef DEBUG_MODE
	m_debugInfo = new DebugInfo();
#endif
}

void GameEngine::CreateListeners()
{
	CharacterDiedListener* characterDiedListener = new CharacterDiedListener(this);
	m_eventEngine->addListener(CHARACTER_DIED, characterDiedListener);
	m_createdListeners.push_back(characterDiedListener);

	ForegroundItemUpdatedListener* foregroundItemUpdatedListener = new ForegroundItemUpdatedListener(this);
	m_eventEngine->addListener(FOREGROUND_ITEM_UPDATED, foregroundItemUpdatedListener);
	m_createdListeners.push_back(foregroundItemUpdatedListener);

	GotLevelInfoListener* gotLevelInfoListener = new GotLevelInfoListener(this);
	m_eventEngine->addListener(GOT_LVL_INFO, gotLevelInfoListener);
	m_createdListeners.push_back(gotLevelInfoListener);

	KeyboardListener* keyboardListener = new KeyboardListener(this);
	m_eventEngine->addListener("graphics.key_event", keyboardListener);
	m_createdListeners.push_back(keyboardListener);

	NewCharacterReadListener* newCharacterReadListener = new NewCharacterReadListener(this);
	m_eventEngine->addListener(NEW_CHARACTER_READ, newCharacterReadListener);
	m_createdListeners.push_back(newCharacterReadListener);

	NewForegroundItemReadListener* newForegroundItemReadListener = new NewForegroundItemReadListener(this);
	m_eventEngine->addListener(NEW_FOREGROUND_ITEM_READ, newForegroundItemReadListener);
	m_createdListeners.push_back(newForegroundItemReadListener);

	NewPipeReadListener* newPipeReadListener = new NewPipeReadListener(this);
	m_eventEngine->addListener(NEW_PIPE_READ, newPipeReadListener);
	m_createdListeners.push_back(newPipeReadListener);
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

#ifdef DEBUG_MODE
	delete m_debugInfo;
#endif
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
			SendCharacterPosition(i);
		}
	}
	DeleteAllDeadCharacters();
}

void GameEngine::ProcessEvent(EngineEvent& _event)
{
	switch (_event.m_type)
	{
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

void GameEngine::UpdateForegroundItem(unsigned int _id, sf::FloatRect _coordinates)
{
	auto DOtoUpdate = m_listForegroundItems.find(_id);
	if (DOtoUpdate != m_listForegroundItems.end() && DOtoUpdate->second != NULL)
		m_listForegroundItems[_id]->SetCoordinates(_coordinates);
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
				Player *mario = new Player(m_eventEngine, "mario", m_initPosMario);
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

void GameEngine::StoreLevelInfo(LevelInfo* _info)
{
	m_collisionHandler->SetLevelSize(_info->size);
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

void GameEngine::KillCharacter(unsigned int _characterID)
{
	for (unsigned int i = 0; i < m_characters.size(); i++)
	{
		if (m_characters[i] != NULL && m_characters[i]->GetID() == _characterID)
		{
			m_characters[i]->MarkAsDead(); // Will be killed at the end of the frame
			break;
		}
	}
}

void GameEngine::DeleteAllDeadCharacters()
{
	for (unsigned int i = 0; i < m_characters.size(); i++)
	{
		if (m_characters[i] != NULL && m_characters[i]->IsDead())
		{
			m_listForegroundItems.erase(m_characters[i]->GetID());

			delete m_characters[i];
			m_characters[i] = NULL;

			if ((int)i == m_indexMario)
				m_indexMario = -1;
		}
	}
}

void GameEngine::UpdateCharacterPosition(MovingObject& _character, float _dt)
{
	unsigned int id = _character.GetID();

	_character.UpdatePosition(_dt);

	sf::Vector2f pos = _character.GetPosition();
	m_listForegroundItems[id]->SetX(pos.x);
	m_listForegroundItems[id]->SetY(pos.y);
}

// Broadcast character's position
void GameEngine::SendCharacterPosition(int _indexCharacter)
{
	MovingObject *character = m_characters[_indexCharacter];
	if (character == NULL || character->IsDead())
		return;

	InfoForDisplay info = character->GetInfoForDisplay();
	Event posInfo(&info);
	m_eventEngine->dispatch(CHAR_POS_UPDATED, &posInfo);
#ifdef DEBUG_MODE
	if (_indexCharacter == m_indexMario)
	{
		*m_debugInfo = character->GetDebugInfo();
		Event debugInfo(m_debugInfo);
		m_eventEngine->dispatch(DEBUG_INFO_UPDATED, &debugInfo);
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
			}
		}
	}

	m_collisionHandler->HandleCollisionsWithMapEdges(_obj);
}
