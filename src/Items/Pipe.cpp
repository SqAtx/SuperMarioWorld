#include "Pipe.hpp"
#include "../Engines/GameEngine.hpp"

const int Pipe::milisecondsBetweenSpawns = 3000;

Pipe::Pipe(std::string _name, sf::Vector2f _coord, int _pipeId, PipeType _type, GameEngine *_g) : DisplayableObject(_name, _coord, NORMAL), m_pipeId(_pipeId), m_type(_type), m_gameEngine(_g)
{
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
	SpawnEnemyIfTimeElapsed();
	MoveEnemyBeingSpawned(_dt);
}

void Pipe::SpawnEnemyIfTimeElapsed()
{
	if (m_enemyBeingSpawned == NULL && m_spawnTimer.getElapsedTime().asMilliseconds() > Pipe::milisecondsBetweenSpawns)
	{
		m_enemyBeingSpawned = new Goomba("goomba", m_coord.x - 16, m_coord.y + 16, DLEFT);
		SendEnemyToGameEngine();
		m_spawnTimer.restart();
	}
}

void Pipe::MoveEnemyBeingSpawned(float _dt)
{

}

void Pipe::SendEnemyToGameEngine()
{
	if (m_enemyBeingSpawned != NULL)
	{
		m_gameEngine->AddCharacterToArray(m_enemyBeingSpawned);
		m_gameEngine->AddForegroundItemToArray(m_enemyBeingSpawned);
		m_enemyBeingSpawned = NULL;
	}
}
