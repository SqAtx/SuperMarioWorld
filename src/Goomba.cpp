#include "Goomba.hpp"

Goomba::Goomba(std::string _name, sf::Vector2f _coord, Direction _dir) : MovingObject(_name, _coord, WALK)
{
	m_facing = _dir;
	Init();
}

Goomba::Goomba(std::string _name, float _x, float _y, Direction _dir) : MovingObject(_name, _x, _y, WALK)
{
	m_facing = _dir;
	Init();
}

void Goomba::Init()
{
	m_previousState = WALK; // Walk when hits the floor
}

Goomba:: ~Goomba()
{

}

InfoForDisplay Goomba::GetInfoForDisplay()
{
	m_reverseSprite = (m_facing == DRIGHT);
	return MovingObject::GetInfoForDisplay();
}

void Goomba::AddOwnAcceleration()
{
	m_acceleration.x = PhysicsConstants::GoombaAcc * (m_facing == DLEFT ? -1 : 1);
}

float Goomba::GetMaxAbsVelocity_X()
{
	return PhysicsConstants::GoombaMaxSpeed_Walk_X;
}

void Goomba::Move(Instruction _inst)
{
	switch (_inst)
	{
		case GO_LEFT:
			m_facing = DLEFT;
			break;
		case GO_RIGHT:
			m_facing = DRIGHT;
			break;
	}
}

