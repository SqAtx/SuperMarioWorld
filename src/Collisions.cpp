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
	if (m_foregroundObjectCoords.size() <= 1)
		return;

	bool collision = false;
	unsigned int id = _obj.GetID();
	sf::FloatRect objCoords = m_foregroundObjectCoords[id];

	// What happens if there is a collision so Mario is moved and there is another one and Mario is moved again ? The first collision would need to be handled again
	for (std::map<unsigned int, sf::Rect<float>>::iterator it = m_foregroundObjectCoords.begin(); it != m_foregroundObjectCoords.end(); ++it)
	{
		if (it->first != id)
			collision = collision | HandleCollisionWithRect(id, it->second);
	}

	if (collision)
	{
		_obj.SetVelY(0);
		_obj.SetJumpState(ONFLOOR);
	}

	// Fall
	if (_obj.GetPosition().y > 432-objCoords.height)
	{
		m_foregroundObjectCoords[id].top = 432 - objCoords.height;
		_obj.SetVelY(0);
		_obj.SetJumpState(ONFLOOR);	
	}

	// Actual fall ;)
	//if (_obj.GetPosition().y > 432)
		//_obj.Kill();

	objCoords = m_foregroundObjectCoords[id];
	sf::Vector2f newPos(objCoords.left, objCoords.top);
	_obj.SetPosition(newPos);
}

bool GameEngine::HandleCollisionWithRect(unsigned int _objId, sf::Rect<float>_ref)
{
	bool collision = false;
	sf::Rect<float> objCoords = m_foregroundObjectCoords[_objId];
	float gap;

	// Obj on top
	if (objCoords.left + objCoords.width > _ref.left && objCoords.left < _ref.left + _ref.width)
	{
		gap = objCoords.top + objCoords.height - _ref.top;
		if (gap > 0)
		{
			objCoords.top -= gap;
			collision = true;
		}
	}

	// Obj on the left
	/*if (!collision && objCoords.top + objCoords.height > _ref.top && objCoords.top < _ref.top + _ref.height)
	{
		gap = objCoords.left + objCoords.width - _ref.left;
		if (gap > 0)
		{
			objCoords.left -= gap;
			collision = true;
		}
	}

	// Obj on the right
	if (!collision && objCoords.top + objCoords.height > _ref.top && objCoords.top < _ref.top + _ref.height)
	{
		gap = _ref.left + _ref.width - objCoords.left;
		if (gap > 0)
		{
			objCoords.left += gap;
			collision = true;
		}
	}

	// Obj under ref
	if (!collision && objCoords.left + objCoords.width > _ref.left && objCoords.left < _ref.left + _ref.width)
	{
		gap = _ref.top + _ref.height - objCoords.top;
		if (gap > 0)
		{
			objCoords.top += gap;
			collision = true;
		}
	}*/

	m_foregroundObjectCoords[_objId] = objCoords;
	return collision;
}

