#include "Pipe.hpp"

const int Pipe::milisecondsBetweenSpawns = 3000;

Pipe::Pipe(std::string _name, sf::Vector2f _coord, int _pipeId, PipeType _type, EventEngine *_eventEngine) : DisplayableObject(_eventEngine, _name, _coord, NORMAL), m_pipeId(_pipeId), m_type(_type)
{
	m_spawnIsOn = true;
	m_enemyBeingSpawned = NULL;
	m_enemyInfo = new InfoForDisplay();
	m_justFinishedSpawn = false;
	m_spawnTimer.restart();
}

Pipe::~Pipe()
{
	delete m_enemyBeingSpawned;
	delete m_enemyInfo;
}

void Pipe::HandleSpawnEnemies(float _dt)
{
	if (m_spawnIsOn)
		SpawnEnemyIfTimeElapsed();

	if (m_enemyBeingSpawned != NULL)
	{
		MoveEnemyBeingSpawned(_dt);
		SendEnemyBeingSpawnedToGFX();

		if (m_justFinishedSpawn)
		{
			RemoveEnemyBeingSpawned();
			m_justFinishedSpawn = false;
		}

		if (m_enemyBeingSpawned != NULL && IsEnemyReadyToLeavePipe())
		{
			PublishEnemyCreation();
			// RemoveEnemyBeingSpawned should be called here but then the enemy will be missing when gfx.Frame() is called, causing the enemy to flicker.
			// So it's called at the next frame, which requires a flag.
			m_justFinishedSpawn = true;
		}
	}
}

void Pipe::SpawnEnemyIfTimeElapsed()
{
	if (m_enemyBeingSpawned == NULL && m_spawnTimer.getElapsedTime().asMilliseconds() > Pipe::milisecondsBetweenSpawns)
	{
		m_enemyBeingSpawned = new DisplayableObject(m_eventEngine, "goomba_fall", m_coord.x + 8, m_coord.y + 8); // Name is for gfx to pick the right sprite name: needs to be the full name as it is in the .rect file

		m_spawnTimer.restart();
	}
}

void Pipe::MoveEnemyBeingSpawned(float _dt)
{
	m_enemyBeingSpawned->Slide(-PhysicsConstants::EnemySpeedInPipe * _dt, 0);
}

void Pipe::SendEnemyBeingSpawnedToGFX()
{
	*m_enemyInfo = m_enemyBeingSpawned->GetInfoForDisplay();
	Event tmpEvent(m_enemyInfo);
	m_eventEngine->dispatch("game.foreground_item_updated", &tmpEvent);
}

void Pipe::PublishEnemyCreation()
{
	if (m_enemyBeingSpawned != NULL)
	{
		Goomba *goombaJustSpawned = new Goomba(m_eventEngine, "goomba", m_enemyBeingSpawned->GetPosition(), DLEFT); // Will be deleted by game engine when character dies
		Event newGoomba(goombaJustSpawned);
		m_eventEngine->dispatch("game.new_character_read", &newGoomba);

		goombaJustSpawned = NULL;
	}
}

void Pipe::RemoveEnemyBeingSpawned()
{
	/* The enemy used to be a simple displayableObject (as seen by GFX), we remove it... */
	Event removeEnemyBeingSpawned(m_enemyBeingSpawned->GetID());
	m_eventEngine->dispatch("game.foreground_item_removed", &removeEnemyBeingSpawned);

	delete m_enemyBeingSpawned;
	m_enemyBeingSpawned = NULL;
}

bool Pipe::IsEnemyReadyToLeavePipe()
{
	return m_enemyBeingSpawned->GetCoordinates().left < m_coord.x - 16;
}
