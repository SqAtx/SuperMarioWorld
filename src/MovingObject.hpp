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

enum JumpState {
	JUMPING,
	REACHINGAPEX, // Phase between the jump and the fall: the object is still rising but without acceleration on the Y axis 
	FALLING,
	ONFLOOR,
	NONE	// At the beginning of the level, for example
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

		virtual InfoForDisplay GetInfoForDisplay();

		void UpdatePosition(float _dt);

		void SetVelX(float _x) { m_velocity.x = _x; };
		void SetVelY(float _y) { m_velocity.y = _y; }
		void SetJumpState(JumpState _state) { m_jumpState = _state; };
		void Kill() { m_isDead = true; };
		bool IsDead() { return m_isDead; };

#ifdef DEBUG_MODE
		DebugInfo GetDebugInfo();
#endif

	protected:
		Direction m_facing;
		JumpState m_jumpState;

		void UpdateAcceleration();
		void UpdateVelocity(float _dt);
		float GetMaxAbsVelocity_X();

		virtual void AddOwnAcceleration() = 0;

		int m_maxSpeed;
		sf::Vector2f m_velocity;
		sf::Vector2f m_acceleration;

		bool m_isDead;
};

#endif