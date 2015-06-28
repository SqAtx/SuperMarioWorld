#ifndef PLAYER_H
#define PLAYER_H

#include "MovingObject.hpp"

class Player : public MovingObject
{
	public:
		Player(std::string _name, sf::Vector2f _coord, State _state = UNKNOWN);
		Player(std::string _name, float _x, float _y, State _state = UNKNOWN);
		~Player();

		void Init();

		InfoForDisplay GetInfoForDisplay();
		virtual void UpdateAfterCollision(CollisionDirection _dir, ObjectClass _classOfOtherObject);

		void ToggleRun(bool _mustRun);

		virtual float GetMaxAbsVelocity_X();
		virtual void Move(Instruction _inst);
		bool Jump();
		void EndJump();

	private:

		virtual void AddOwnAcceleration();

		bool m_canJump; // To avoid Mario jumping around if the jump key is pressed and held
};

#endif