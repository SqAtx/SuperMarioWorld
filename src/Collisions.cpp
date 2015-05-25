#include "GameEngine.hpp"

void GameEngine::HandleCollisionsWithMapEdges(MovingObject& _obj)
{
	if (_obj.GetPosition().x < 0)
	{
		_obj.SetX(0);
		_obj.SetVelX(0);
	}
	if (_obj.GetPosition().x > 512 - 13)
	{
		_obj.SetX(512 - 13);
		_obj.SetVelX(0);
	}
}

void GameEngine::HandleCollisionsWithLevel(MovingObject& _obj)
{
	sf::Rect<float> objCoords = m_foregroundObjectCoords[_obj.GetID()];
	/*if (_obj.GetPosition().y > 432 - 16 - objCoords.height && (_obj.GetPosition().x < 140 || _obj.GetPosition().x > 196))
	{
		_obj.SetY(432 - 16 - objCoords.height);
		_obj.SetVelY(0);
		_obj.SetJumpState(ONFLOOR);
	}*/

	// Fall
	if (_obj.GetPosition().y > 432-objCoords.height)
	{
		_obj.SetY(432-objCoords.height);
		_obj.SetVelY(0);
		_obj.SetJumpState(ONFLOOR);
		//_obj.Kill();
	}
}

