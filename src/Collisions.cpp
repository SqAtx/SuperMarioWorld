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
	if (_obj.GetPosition().y > 432 - 16 && (_obj.GetPosition().x < 140 || _obj.GetPosition().x > 196))
	{
		_obj.SetY(432 - 16);
		_obj.SetVelY(0);
		_obj.SetJumpState(ONFLOOR);
	}
	if (_obj.GetPosition().y > 432)
	{
		//_obj.SetY(432);
		//_obj.SetJumpState(ONFLOOR);
		_obj.Kill();
	}
}