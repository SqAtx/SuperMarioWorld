#include "Pipe.hpp"
#include "../Engines/GameEngine.hpp"

const int Pipe::milisecondsBetweenSpawns = 3000;

Pipe::Pipe(std::string _name, sf::Vector2f _coord, int _pipeId, PipeType _type, GameEngine *_g) : DisplayableObject(_name, _coord, NORMAL), m_pipeId(_pipeId), m_type(_type), m_gameEngine(_g)
{
	m_spawnIsOn = true;
	m_enemyBeingSpawned = NULL;
	m_spawnTimer.restart();
}

Pipe::~Pipe()
{
	delete m_enemyBeingSpawned;
	delete m_gameEngine;
}

void Pipe::HandleSpawnEnemies(float _dt)
{
	if (m_spawnIsOn)
		SpawnEnemyIfTimeElapsed();

	if (m_enemyBeingSpawned != NULL)
	{
		MoveEnemyBeingSpawned(_dt);
		SendEnemyBeingSpawnedToGFX();

		if (m_enemyBeingSpawned->GetPosition().x < m_coord.x - 16)
			SendEnemyToGameEngine();
	}
}

void Pipe::SpawnEnemyIfTimeElapsed()
{
	if (m_enemyBeingSpawned == NULL && m_spawnTimer.getElapsedTime().asMilliseconds() > Pipe::milisecondsBetweenSpawns)
	{
		//m_enemyBeingSpawned = new Goomba("goomba", m_coord.x + 8, m_coord.y + 8, DLEFT);
		m_enemyBeingSpawned = new DisplayableObject("goomba_fall", m_coord.x + 8, m_coord.y + 8); // Game is for gfx to pick the right sprite name: needs to be the full name as it is in the .rect file

		m_spawnTimer.restart();
	}
}

void Pipe::MoveEnemyBeingSpawned(float _dt)
{
	m_enemyBeingSpawned->Slide(-PhysicsConstants::EnemySpeedInPipe * _dt, 0);
}

void Pipe::SendEnemyBeingSpawnedToGFX()
{
	EngineEvent tmpEvent(INFO_POS_LVL, m_enemyBeingSpawned->GetInfoForDisplay());
	m_gameEngine->TransmitInfoToGFX(tmpEvent);
}

void Pipe::SendEnemyToGameEngine()
{
	if (m_enemyBeingSpawned != NULL)
	{
		/* The enemy used to be a mere displayableObject (as seen by GFX), we remove it... */
		EngineEvent removeEnemyBeingSpawned(REMOVE_LVL_BLOC, m_enemyBeingSpawned->GetID());
		m_gameEngine->TransmitInfoToGFX(removeEnemyBeingSpawned);

		/*  and send the actual Enemy to G */
		Goomba *goombaJustSpawned = new Goomba("goomba", m_enemyBeingSpawned->GetPosition(), DLEFT);
		m_gameEngine->AddCharacterToArray(goombaJustSpawned);
		m_gameEngine->AddForegroundItemToArray(goombaJustSpawned);

		goombaJustSpawned = NULL;
		delete m_enemyBeingSpawned;
		m_enemyBeingSpawned = NULL;
	}
}
