#include "Player.hpp"

Player::Player(std::string _name, sf::Vector2f _coord) : MovingObject(_name, _coord)
{
	Init();
}

Player::Player(std::string _name, float _x, float _y) : MovingObject(_name, _x, _y)
{
	Init();
}

void Player::Init()
{
	m_facing = DRIGHT;
}

Player:: ~Player()
{

}

InfoForDisplay Player::GetInfoForDisplay()
{
	m_reverseSprite = (m_facing == DLEFT);
	return MovingObject::GetInfoForDisplay();
}


/*
*	TEST, not pretty, could be refactored too, but very temporary anyway :)
*/
void Player::move(int _a)
{
	if (_a > 0)
	{
		m_acceleration.x = PhysicsConstants::PlayerAcc;
		if (m_facing == DLEFT)
			m_velocity.x = 0; // Player should skid
		m_facing = DRIGHT;
	}
	else if (_a < 0)
	{
		m_acceleration.x = -PhysicsConstants::PlayerAcc;
		if (m_facing == DRIGHT)
			m_velocity.x = 0; // Player should skid
		m_facing = DLEFT;
	}
	else
	{
		m_acceleration.x = 0;
	}
}