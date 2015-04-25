#include "MovingObject.hpp"

MovingObject::MovingObject(std::string _name, sf::Vector2f _coord) : DisplayableObject(_name, _coord)
{
	Init();
}

MovingObject::MovingObject(std::string _name, float _x, float _y) : DisplayableObject(_name, _x, _y)
{
	Init();
}

void MovingObject::Init()
{
	m_maxSpeed = 0;
	m_velocity = { 0, 0 };
	m_acceleration = { 0, PhysicsConstants::Gravity};
}

MovingObject::~MovingObject()
{

}

/*
*	To be refactored, this is just for basic testing and displaying something fun
*/
void MovingObject::UpdatePosition(float _dt)
{
	m_velocity = {
		m_velocity.x += m_acceleration.x * _dt,
		m_velocity.y += m_acceleration.y * _dt,
	};

	if (m_velocity.x > PhysicsConstants::PlayerMaxSpeed_X)
		m_velocity.x = PhysicsConstants::PlayerMaxSpeed_X;
	if (m_velocity.x < -PhysicsConstants::PlayerMaxSpeed_X)
		m_velocity.x = -PhysicsConstants::PlayerMaxSpeed_X;

	m_coord = {
		m_coord.x += m_velocity.x * _dt,
		m_coord.y += m_velocity.y * _dt,
	};

	/*
	*	Very basic collision handling, shouldn't be here; only for testing =)
	*/
	if (m_coord.x < 0)
	{
		m_coord.x = 0;
		m_velocity.x = 0;
	}
	if (m_coord.x > 512 - 13)
	{
		m_coord.x = 512 - 13;
		m_velocity.x = 0;
	}
	if (m_coord.y > 432 - 16)
	{
		m_coord.y = 432 - 16;
		m_velocity.y = 0;
	}

	// Basic friction too, so Mario stops instead of skidding endlessly
	if (m_acceleration.x == 0)
	{
		m_velocity.x *= 0.9;
		if (abs(m_velocity.x) < 5)
			m_velocity.x /= 2;
		if (abs(m_velocity.x) < 0.5)
			m_velocity.x = 0;
	}

	// If Mario is not moving, his state should be STATIC
	if (m_velocity.x == 0)
		m_state = STATIC;
}

#ifdef DEBUG_MODE
DebugInfo MovingObject::GetDebugInfo()
{
	DebugInfo info;
	info.velocity = m_velocity;
	info.acceleration = m_acceleration;
	return info;
}
#endif