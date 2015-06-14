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

		void ToggleRun(bool _mustRun);

		void Move(int);
		bool Jump();
		void EndJump();

	private:

		void AddOwnAcceleration();

		bool m_canJump; // To avoid Mario jumping around if the jump key is pressed and held
};

#endif