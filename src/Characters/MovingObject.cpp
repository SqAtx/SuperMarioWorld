#include "MovingObject.hpp"

MovingObject::MovingObject(std::string _name, sf::Vector2f _coord, State _state) : DisplayableObject(_name, _coord, _state), m_noCollision(false)
{
	Init();
}

MovingObject::MovingObject(std::string _name, float _x, float _y, State _state) : DisplayableObject(_name, _x, _y, _state), m_noCollision(false)
{
	Init();
}

void MovingObject::Init()
{
	m_maxSpeed = 0;
	m_velocity = { 0, 0 };
	m_acceleration = { 0, PhysicsConstants::Gravity};
	m_jumpState = NONE;
	m_previousState = UNKNOWN;
	m_isDead = false;
}

MovingObject::~MovingObject()
{

}

InfoForDisplay MovingObject::GetInfoForDisplay()
{
	InfoForDisplay info = DisplayableObject::GetInfoForDisplay();
	if (m_jumpState == JUMPING || m_jumpState == REACHINGAPEX)
		info.state = JUMP; // This state is for GraphicsEngine to know which sprite to display. GameEngine still needs to make a difference between "Jump and Walk" and "Jump and Run"
	if (m_jumpState == FALLING)
		info.state = FALL;
	return info;
}

void MovingObject::UpdateAfterCollisionWithMapEdge(CollisionDirection _dir, float _gap)
{
	switch (_dir)
	{
		case LEFT:
			m_coord.x = 0;
			m_velocity.x = 0;
			break;
		case RIGHT:
			m_coord.x -= _gap;
			m_velocity.x = 0;
			break;
		default:
			break;
	}
}


void MovingObject::UpdatePosition(float _dt)
{
	/* Before velocity calculation, not after, otherwise the character (when walking) will be falling before its collision with the ground is handled again */
	if (m_velocity.y > 0)
		m_jumpState = FALLING;
	
	UpdateAcceleration();
	UpdateVelocity(_dt);

	if (m_acceleration.x == 0)
		m_state = STATIC;

	m_coord = {
		m_coord.x += m_velocity.x * _dt,
		m_coord.y += m_velocity.y * _dt,
	};
}

void MovingObject::UpdateAcceleration()
{
	m_acceleration.x = 0;
	m_acceleration.y = PhysicsConstants::Gravity;

	AddOwnAcceleration();

	switch (m_jumpState)
	{
		/*
		*	Friction of floor
		*	P + n + f = ma, with a the acceleration resulting from friction. I removed the "own acceleration" (which should be A = F * const, so the same on both sides of the equation).
		*	On x axis: 0 + 0 + uN = ma ==> ug = a
		*/
		case ONFLOOR:
			if (m_acceleration.x == 0 && abs(m_velocity.x) >= PhysicsConstants::MinSpeed)
				m_acceleration.x += PhysicsConstants::FrictionPlayerGound * PhysicsConstants::Gravity * (m_facing == DLEFT ? 1 : -1);
			break;

		// In the air, simplified fluid model: friction force is proportional to velocity. a  = F/m, an acceleration is also sort of proporional to a force
		case JUMPING:
		case REACHINGAPEX:
		case FALLING:
			m_acceleration.x -= PhysicsConstants::FrictionPlayerAir * m_velocity.x;
			m_acceleration.y -= PhysicsConstants::FrictionPlayerAir * m_velocity.y;
			break;

		case NONE:
		default:
			break;
	}
}

void MovingObject::UpdateVelocity(float _dt)
{
	m_velocity = {
		m_velocity.x += m_acceleration.x * _dt,
		m_velocity.y += m_acceleration.y * _dt,
	};

	// Check for maximum velocity on X
	float maxAbsVel = GetMaxAbsVelocity_X();
	if (m_velocity.x > maxAbsVel)
		m_velocity.x = maxAbsVel;
	if (m_velocity.x < -maxAbsVel)
		m_velocity.x = -maxAbsVel;

	// Make sure the player is not running backwards (which can happen when the friction force creates a big acceleration in the opposite direction)
	if (!IsInTheAir() && ( (m_facing == DLEFT && m_velocity.x > 0) || (m_facing == DRIGHT && m_velocity.x < 0)))
		m_velocity.x = 0;

	if (abs(m_velocity.x) < PhysicsConstants::MinSpeed)
		m_velocity.x = 0;
}

#ifdef DEBUG_MODE
DebugInfo MovingObject::GetDebugInfo()
{
	DebugInfo info;
	info.velocity = m_velocity;
	info.acceleration = m_acceleration;
	info.state = m_state;
	info.jumpState = m_jumpState;
	return info;
}
#endif
