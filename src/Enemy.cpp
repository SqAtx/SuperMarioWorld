#include "Enemy.hpp"

Enemy::Enemy(std::string _name, sf::Vector2f _coord, Direction _dir) : MovingObject(_name, _coord, WALK)
{
	m_facing = _dir;
}

Enemy::Enemy(std::string _name, float _x, float _y, Direction _dir) : MovingObject(_name, _x, _y, WALK)
{
	m_facing = _dir;
}

InfoForDisplay Enemy::GetInfoForDisplay()
{
	m_reverseSprite = (m_facing == DRIGHT);
	return MovingObject::GetInfoForDisplay();
}

void Enemy::UpdateAfterCollisionWithMapEdge(CollisionDirection _dir, float _gap)
{
	switch (_dir)
	{
		case LEFT: // Enemy on the left (= right hand edge)
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

void Enemy::Move(Instruction _inst)
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

