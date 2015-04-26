#ifndef CHARACTER_H
#define CHARACTER_H

#include "DisplayableObject.hpp"

#ifdef DEBUG_MODE
struct DebugInfo {
	sf::Vector2f velocity;
	sf::Vector2f acceleration;
};
#endif

enum Direction {
	DLEFT,
	DRIGHT
};

/*
*	A MovingObject can be a player, an enemy, or a moving item, such as a power-up
*/
class MovingObject : public DisplayableObject
{
	public:
		MovingObject(std::string _name, sf::Vector2f _coord);
		MovingObject(std::string _name, float _x, float _y);
		~MovingObject();

		void Init();

		void UpdatePosition(float _dt);

#ifdef DEBUG_MODE
		DebugInfo GetDebugInfo();
#endif

	protected:
		Direction m_facing;

		void UpdateAcceleration();
		void UpdateVelocity(float _dt);
			float GetMaxAbsVelocity_X();
		void HandleCollisionsWithMapEdges();
		void HandleCollisionsWithLevel();

		virtual void AddOwnAcceleration() = 0;

		int m_maxSpeed;
		sf::Vector2f m_velocity;
		sf::Vector2f m_acceleration;
};

#endif