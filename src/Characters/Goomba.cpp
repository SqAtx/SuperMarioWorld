#include "Goomba.hpp"

Goomba::Goomba(std::string _name, sf::Vector2f _coord, Direction _dir) : Enemy(_name, _coord, _dir)
{

}

Goomba::Goomba(std::string _name, float _x, float _y, Direction _dir) : Enemy(_name, _x, _y, _dir)
{

}

void Goomba::UpdateAfterCollision(CollisionDirection _dir, ObjectClass _classOfOtherObject)
{
	switch (_dir)
	{
		case TOP:
			m_velocity.y = 0;
			m_jumpState = FALLING;

			if (_classOfOtherObject == PLAYER)
			{
				m_noCollision = true; // No collision with anything will kill it when it reaches the bottom edge of the map
				m_velocity.x = 0;
				m_velocity.y = PhysicsConstants::GoombaMaxSpeed_Walk_X;
			}
			break;
		case BOTTOM:
			m_state = WALK;

			m_velocity.y = 0;
			m_jumpState = ONFLOOR;
			break;
		case LEFT:
			m_facing = DRIGHT;
			m_velocity.x = 0;
			m_jumpState = FALLING;
			break;
		case RIGHT:
			m_facing = DLEFT;
			m_velocity.x = 0;
			m_jumpState = FALLING;
			break;
		case NO_COL:
		default:
			break;
	}
}

void Goomba::AddOwnAcceleration()
{
	m_acceleration.x = PhysicsConstants::GoombaAcc * (m_facing == DLEFT ? -1 : 1);
}

float Goomba::GetMaxAbsVelocity_X()
{
	return PhysicsConstants::GoombaMaxSpeed_Walk_X;
}
