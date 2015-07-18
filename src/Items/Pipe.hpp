#ifndef PIPE_H
#define PIPE_H

#include "../DisplayableObject.hpp"
#include <SFML\System\Clock.hpp>

class GameEngine;
class Enemy;

/*
*	A Pipe can be used to travel, to spawn enemies
*/
class Pipe : public DisplayableObject
{
	public:
		Pipe(std::string _name, sf::Vector2f _coord, int _pipeId, PipeType _type, GameEngine *_g);
		~Pipe();
		
		void Pipe::HandleSpawnEnemies(float _dt);

		unsigned int GetPipeId() { return m_pipeId; };
		PipeType GetPipeType() { return m_type; };

	protected:
		unsigned int m_pipeId;
		PipeType m_type;

		DisplayableObject *m_enemyBeingSpawned; // One enemy at a time can be spawed and controlled by the pipe
		sf::Clock m_spawnTimer;

		GameEngine *m_gameEngine;

		void MoveEnemyBeingSpawned(float _dt);
		void SpawnEnemyIfTimeElapsed();
		void SendEnemyBeingSpawnedToGFX();
		void SendEnemyToGameEngine();

		static const int milisecondsBetweenSpawns;
};

#endif
