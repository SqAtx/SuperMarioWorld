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

}

Goomba:: ~Goomba()
{

}

InfoForDisplay Goomba::GetInfoForDisplay()
{
	m_reverseSprite = (m_facing == DRIGHT);
	return MovingObject::GetInfoForDisplay();
}

void Goomba::UpdateAfterCollision(CollisionDirection _dir)
{
	switch (_dir)
	{
		case TOP:
			m_state = WALK;

			m_velocity.y = 0;
			m_jumpState = ONFLOOR;
			break;
		case BOTTOM:
			m_velocity.y = 0;
			m_jumpState = FALLING;
			break;
		case LEFT:
			m_facing = DLEFT;
			m_velocity.x = 0;
			m_jumpState = FALLING;
			break;
		case RIGHT:
			m_facing = DRIGHT;
			m_velocity.x = 0;
			m_jumpState = FALLING;
			break;
		case NO_COL:
		default:
			break;
	}
}

void Goomba::UpdateAfterCollisionWithMapEdge(CollisionDirection _dir, float _gap)
{
	switch (_dir)
	{
		case LEFT: // Goomba on the left
			m_facing = DLEFT;
			break;
		case RIGHT:
			m_facing = DRIGHT;
			break;
		default:
			break;
	}
	MovingObject::UpdateAfterCollisionWithMapEdge(_dir, _gap);
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

