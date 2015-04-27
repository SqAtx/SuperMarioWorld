#ifndef PLAYER_H
#define PLAYER_H

#include "MovingObject.hpp"

class Player : public MovingObject
{
	public:
		Player(std::string _name, sf::Vector2f _coord);
		Player(std::string _name, float _x, float _y);
		~Player();

		void Init();

		InfoForDisplay GetInfoForDisplay();

		void ToggleRun(bool _mustRun);

		void Move(int);
		void Jump();

	private:

		void AddOwnAcceleration();

		bool m_isRunning;
};

#endif