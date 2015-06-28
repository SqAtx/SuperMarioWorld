#include "GameEngine.hpp"

void GameEngine::HandleCollisionsWithMapEdges(MovingObject& _obj)
{
	unsigned int objId = _obj.GetID();
	sf::FloatRect objCoords = m_listForegroundItems[objId]->GetCoordinates();

	if (_obj.GetPosition().x < 0)
	{
		_obj.UpdateAfterCollisionWithMapEdge(CollisionDirection::RIGHT, _obj.GetPosition().x); // RIGHT to be consistent with collision: the player is on the right
	}
	if (_obj.GetPosition().x > 512 - 13)
	{
		_obj.UpdateAfterCollisionWithMapEdge(CollisionDirection::LEFT, _obj.GetPosition().x - (512-13));
	}

	// Debug Fall
	//if (_obj.GetPosition().y > 432-objCoords.height)
	//{
	//	_obj.SetY(432 - objCoords.height);
	//	_obj.SetVelY(0);
	//	_obj.SetJumpState(ONFLOOR);	
	//}

	// Actual fall ;)
	if (_obj.GetPosition().y > 432)
		_obj.Kill();
}

void GameEngine::HandleCollisionsWithLevel(MovingObject& _obj)
{
	if (m_listForegroundItems.size() <= 1)
		return;

	DisplayableObject* objectHitByChar;
	CollisionDirection tmpDirection = NO_COL, lastCollisionDirection = NO_COL;
	unsigned int objId = _obj.GetID(), lastCollisionRefId = 0;
	sf::FloatRect objCoords = m_listForegroundItems[objId]->GetCoordinates();

	// What happens if there is a collision so _obj is moved and there is another one and _obj is moved again ? The first collision would need to be handled again
	for (std::map<unsigned int, DisplayableObject*>::iterator it = m_listForegroundItems.begin(); it != m_listForegroundItems.end(); ++it)
	{
		if (it->first != objId)
		{
			tmpDirection = HandleCollisionWithRect(objId, it->second->GetCoordinates());
			if (tmpDirection != NO_COL)
			{
				lastCollisionDirection = tmpDirection;
				lastCollisionRefId = it->first;
			}
		}
	}

	if (lastCollisionDirection != NO_COL)
	{
		objectHitByChar = m_listForegroundItems[lastCollisionRefId];

		_obj.UpdateAfterCollision(Util::OppositeCollisionDirection(lastCollisionDirection), objectHitByChar->GetClass()); // Updates the state of the object, not his coordinates

		// The coordinates (of the element of m_listForegroundItems) have been changed in HandleCollisionWithRect: we copy that into the object (element of m_characters)
		objCoords = m_listForegroundItems[objId]->GetCoordinates();
		sf::Vector2f newPos(objCoords.left, objCoords.top);
		_obj.SetPosition(newPos);

		objectHitByChar->UpdateAfterCollision(lastCollisionDirection, _obj.GetClass());

		// Send information about the object that has been hit (for gfx to know about states changes)
		EngineEvent redisplayObject;
		redisplayObject.m_type = INFO_POS_LVL;
		for(int i = 0; i < m_characters.size(); i++)
		{
			// objectHitByChar is a character
			if (m_characters[i] != NULL && m_characters[i]->GetID() == objectHitByChar->GetID()) /* m_characters[i] can be null if a character just died */
			{
				redisplayObject.set(INFO_POS_CHAR, objectHitByChar->GetInfoForDisplay());
				break;
			}
		}
		if (redisplayObject.m_type == INFO_POS_LVL) // If redisplayObject hasn't been set, ie objectHitByChar is not a character
			redisplayObject.set(INFO_POS_LVL, objectHitByChar->GetInfoForDisplay());
		m_engines["gfx"]->PushEvent(redisplayObject);
	}
}

CollisionDirection GameEngine::HandleCollisionWithRect(unsigned int _objId, sf::FloatRect _ref)
{
	CollisionDirection direction = DetectCollisionWithRect(_objId, _ref);
	ReactToCollision(_objId, _ref, direction);
	return direction;
}

CollisionDirection GameEngine::DetectCollisionWithRect(unsigned int _objId, sf::FloatRect _ref)
{
	CollisionDirection direction = NO_COL;
	sf::Rect<float> objCoords = m_listForegroundItems[_objId]->GetCoordinates();

	/* If TOP or BOTTOM collisions are possible */
	if ((objCoords.left <= _ref.left && objCoords.left + objCoords.width > _ref.left)
		|| (objCoords.left < _ref.left + _ref.width && objCoords.left + objCoords.width >= _ref.left + _ref.width)
		|| (objCoords.left >= _ref.left && objCoords.left + objCoords.width <= _ref.left + _ref.width))
	{
		if (objCoords.top < _ref.top && objCoords.top + objCoords.height > _ref.top)
			direction = TOP;
		if (objCoords.top < _ref.top + _ref.height && objCoords.top + objCoords.height > _ref.top + _ref.height)
			direction = BOTTOM;
	}

	/* If LEFT or RIGHT collisions are possible */
	if ((objCoords.top <= _ref.top && objCoords.top + objCoords.height > _ref.top)
		|| (objCoords.top < _ref.top + _ref.height && objCoords.top + objCoords.height >= _ref.top + _ref.height)
		|| (objCoords.top >= _ref.top && objCoords.top + objCoords.height <= _ref.top + _ref.height))
	{
		/* Collision on LEFT but there may be TOP or BOTTOM as well */
		if (objCoords.left < _ref.left && objCoords.left + objCoords.width > _ref.left)
		{
			if (direction == TOP && objCoords.top + objCoords.height - _ref.top < objCoords.left + objCoords.width - _ref.left)
				direction = TOP;
			else if (direction == BOTTOM && _ref.top + _ref.height - objCoords.top < objCoords.left + objCoords.width - _ref.left)
				direction = BOTTOM;
			else
				direction = LEFT;
		}

		/* Collision on RIGHT but there may be TOP or BOTTOM as well */
		if (objCoords.left < _ref.left +_ref.width && objCoords.left + objCoords.width > _ref.left + _ref.width)
		{
			if (direction == TOP && objCoords.top + objCoords.height - _ref.top < _ref.left + _ref.width - objCoords.left)
				direction = TOP;
			else if (direction == BOTTOM && _ref.top + _ref.height - objCoords.top < _ref.left + _ref.width - objCoords.left)
				direction = BOTTOM;
			else
				direction = RIGHT;
		}
	}

	return direction;
}

void GameEngine::ReactToCollision(unsigned int _objId, sf::FloatRect _ref, CollisionDirection _direction)
{
	sf::Rect<float> objCoords = m_listForegroundItems[_objId]->GetCoordinates();
	switch (_direction)
	{
		case TOP:
			objCoords.top -= (objCoords.top + objCoords.height - _ref.top);
			break;
		case BOTTOM:
			objCoords.top += (_ref.top + _ref.height - objCoords.top);
			break;
		case LEFT:
			objCoords.left -= (objCoords.left + objCoords.width - _ref.left);
			break;
		case RIGHT:
			objCoords.left += (_ref.left + _ref.width - objCoords.left);
			break;
		case NO_COL:
		default:
			break;
	}
	m_listForegroundItems[_objId]->SetCoordinates(objCoords);
}
