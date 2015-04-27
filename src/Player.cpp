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
	switch (m_state)
	{
		case WALK:
			m_acceleration.x = PhysicsConstants::PlayerAcc_Walk * (m_facing == DLEFT ? -1 : 1);
			break;
		case RUN:
			m_acceleration.x = PhysicsConstants::PlayerAcc_Run * (m_facing == DLEFT ? -1 : 1);
			break;
	}

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
		//if (m_facing == DLEFT)
			//m_velocity.x = 0; // Player should skid
		m_facing = DRIGHT;

		m_state = m_isRunning ? RUN : WALK;
	}
	else if (_a < 0)
	{
		//if (m_facing == DRIGHT)
			//m_velocity.x = 0; // Player should skid
		m_facing = DLEFT;

		m_state = m_isRunning ? RUN : WALK;
	}
	else
		m_state = STATIC;
}

void Player::Jump()
{
	if (m_jumpState == ONFLOOR && m_canJump)
	{
		m_jumpState = JUMPING;
		m_canJump = false;
	}
}

// This is called when the jump key is released, so the player doesn't keep jumping around if the key stays down
void Player::EndJump()
{
	m_canJump = true;
}