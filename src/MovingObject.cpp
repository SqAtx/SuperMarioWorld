#include "MovingObject.hpp"

MovingObject::MovingObject(std::string _name, sf::Vector2f _coord, State _state) : DisplayableObject(_name, _coord, _state)
{
	Init();
}

MovingObject::MovingObject(std::string _name, float _x, float _y, State _state) : DisplayableObject(_name, _x, _y, _state)
{
	Init();
}

void MovingObject::Init()
{
	m_maxSpeed = 0;
	m_velocity = { 0, 0 };
	m_acceleration = { 0, PhysicsConstants::Gravity};
	m_jumpState = NONE;
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

void MovingObject::UpdatePosition(float _dt)
{
	UpdateAcceleration();
	UpdateVelocity(_dt);

	if (m_acceleration.x == 0)
		m_state = STATIC;

	if (m_velocity.y > 0 && m_jumpState != ONFLOOR) // Can't go from ONFLOOR to FALLING (character would be FALLING before collision handling otherwise)
		m_jumpState = FALLING;

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
		*	On x axis: 0 + 0 + µN = ma ==> µg = a
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
	}
}

void MovingObject::UpdateVelocity(float _dt)
{
	m_velocity = {
		m_velocity.x += m_acceleration.x * _dt,
		m_velocity.y += m_acceleration.y * _dt,
	};

	// Check for maximum velocity
	float maxAbsVel = GetMaxAbsVelocity_X();
	if (m_velocity.x > maxAbsVel)
		m_velocity.x = maxAbsVel;
	if (m_velocity.x < -maxAbsVel)
		m_velocity.x = -maxAbsVel;

	// Make sure the player is not running backwards (which can happen when the friction force creates a big acceleration in the opposite direction)
	if (!IsInTheAir() && (m_facing == DLEFT && m_velocity.x > 0 || m_facing == DRIGHT && m_velocity.x < 0))
		m_velocity.x = 0;

	if (abs(m_velocity.x) < PhysicsConstants::MinSpeed)
		m_velocity.x = 0;
}

float MovingObject::GetMaxAbsVelocity_X()
{
	switch (m_state)
	{
		case WALK:
			return PhysicsConstants::PlayerMaxSpeed_Walk_X;
		case RUN:
			return PhysicsConstants::PlayerMaxSpeed_Run_X;
		default:
			return PhysicsConstants::PlayerMaxSpeed_Run_X;;
	}
}

void MovingObject::UpdateAfterCollision(CollisionDirection _dir)
{
	switch (_dir)
	{
		case TOP:
			if (m_jumpState != ONFLOOR) // Landing
				m_state = m_previousState;

			m_velocity.y = 0;
			m_jumpState = ONFLOOR;
			break;
		case BOTTOM:
			m_velocity.y = 0;
			m_jumpState = FALLING;
			break;
		case LEFT:
			m_velocity.x = 0;
			m_jumpState = FALLING;
			break;
		case RIGHT:
			m_velocity.x = 0;
			m_jumpState = FALLING;
			break;
		case NO_COL:
		default:
			break;
	}
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