#include "Player.hpp"

Player::Player(std::string _name, sf::Vector2f _coord, State _state) : MovingObject(_name, _coord, _state)
{
	Init();
}

Player::Player(std::string _name, float _x, float _y, State _state) : MovingObject(_name, _x, _y, _state)
{
	Init();
}

void Player::Init()
{
	m_facing = DRIGHT;
	m_isRunning = false;
	m_canJump = true;
}

Player:: ~Player()
{

}

InfoForDisplay Player::GetInfoForDisplay()
{
	m_reverseSprite = (m_facing == DLEFT);
	return MovingObject::GetInfoForDisplay();
}

void Player::AddOwnAcceleration()
{
	// Player keeps acceleration when jumping
	if (m_state == WALK || (IsInTheAir() && m_previousState == WALK))
		m_acceleration.x = PhysicsConstants::PlayerAcc_Walk * (m_facing == DLEFT ? -1 : 1);
	if (m_state == RUN || (IsInTheAir() && m_previousState == RUN))
		m_acceleration.x = PhysicsConstants::PlayerAcc_Run * (m_facing == DLEFT ? -1 : 1);

	// Takes off if enough speed on the Y axis
	if (m_jumpState == JUMPING)
	{
		if (abs(m_velocity.y) < PhysicsConstants::MinSpeed) // Little push at the beginning of the jump
			m_velocity.y -= PhysicsConstants::InitialYVelForJump;
		if (abs(m_velocity.y) < PhysicsConstants::MaxYVelForJump)
			m_acceleration.y += PhysicsConstants::PlayerJumpAcc;
		else
			m_jumpState = REACHINGAPEX;
	}
}

void Player::ToggleRun(bool _mustRun)
{
	if (_mustRun && m_state == WALK)
		m_state = RUN;
	if (!_mustRun && m_state == RUN)
		m_state = WALK;
	m_isRunning = _mustRun;
}

void Player::Move(int _a)
{
	if (_a > 0)
	{
		m_facing = DRIGHT;
		m_state = m_isRunning ? RUN : WALK;
	}
	else if (_a < 0)
	{
		m_facing = DLEFT;
		m_state = m_isRunning ? RUN : WALK;
	}
	else
	{
		m_state = STATIC;

		if (IsInTheAir())
			m_previousState = STATIC;
	}
 }

bool Player::Jump()
{
	if (m_jumpState == ONFLOOR && m_canJump)
	{
		m_jumpState = JUMPING;
		m_previousState = m_state;
		m_canJump = false;
		return true;
	}
	return false;
}

// This is called when the jump key is released, so the player doesn't keep jumping around if the key stays down
void Player::EndJump()
{
	m_canJump = true;
}