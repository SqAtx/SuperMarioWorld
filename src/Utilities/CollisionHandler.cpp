#include "CollisionHandler.hpp"
#include "../Engines/GameEngine.hpp"


CollisionHandler::CollisionHandler(GameEngine *_parent)
{
	m_gameEngine = _parent;
}

CollisionHandler::~CollisionHandler()
{
	delete m_gameEngine;
}

void CollisionHandler::HandleCollisionsWithMapEdges(MovingObject& _obj)
{
	if (_obj.GetPosition().x < 0)
	{
		_obj.UpdateAfterCollisionWithMapEdge(CollisionDirection::LEFT, _obj.GetPosition().x);
	}
	float gapRightEdge = _obj.GetPosition().x - (m_levelSize.x - _obj.GetCoordinates().width);
	if (gapRightEdge > 0)
	{
		_obj.UpdateAfterCollisionWithMapEdge(CollisionDirection::RIGHT, gapRightEdge);
	}

	if (_obj.GetPosition().y > m_levelSize.y)
		_obj.Kill();
}

CollisionDirection CollisionHandler::DetectCollisionWithObj(MovingObject& _obj, DisplayableObject& _ref)
{
	if (_obj.GetID() == _ref.GetID())
		return NO_COL;

	return DetectCollisionWithRect(_obj.GetCoordinates(), _ref.GetCoordinates());
}

void CollisionHandler::ReactToCollisionsWithObj(MovingObject& _obj, DisplayableObject& _ref, CollisionDirection _direction)
{
	ReactToCollision(_obj, _ref.GetCoordinates(), _direction);

	_obj.UpdateAfterCollision(Util::OppositeCollisionDirection(_direction), _ref.GetClass()); // Updates the state of the object, not its coordinates
	_obj.SetPosition(m_gameEngine->GetCoordinatesOfForegroundItem(_obj.GetID()));

	_ref.UpdateAfterCollision(_direction, _obj.GetClass());

	SendNewObjectPositionToGFX(_ref);
}

void CollisionHandler::SendNewObjectPositionToGFX(DisplayableObject& _obj)
{
	// Send information about the object that has been hit (for gfx to know about states changes)
	EngineEvent redisplayObject(INFO_POS_LVL);
	if (_obj.GetClass() == PLAYER || _obj.GetClass() == ENEMY)
		redisplayObject.set(INFO_POS_CHAR, _obj.GetInfoForDisplay());
	else
		redisplayObject.set(INFO_POS_LVL, _obj.GetInfoForDisplay());
	m_gameEngine->TransmitInfoToGFX(redisplayObject);
}

CollisionDirection CollisionHandler::HandleCollisionWithRect(unsigned int _objId, sf::FloatRect _ref)
{
	DisplayableObject *obj = m_gameEngine->GetForegroundItem(_objId);
	CollisionDirection direction = DetectCollisionWithRect(obj->GetCoordinates(), _ref);
	ReactToCollision(*obj, _ref, direction);
	return direction;
}

/* The result is with respect to the reference: if the object is on its right then the result will be RIGHT */
CollisionDirection CollisionHandler::DetectCollisionWithRect(sf::FloatRect _objRect, sf::FloatRect _refRect)
{
	CollisionDirection direction = NO_COL;
	float minGap = 5; // Minimum gap, in pixels, for the function to consider there can be a collision.

	/* Clarity */
	float objTop = _objRect.top;
	float objBot = _objRect.top + _objRect.height;
	float objLeft = _objRect.left;
	float objRight = _objRect.left + _objRect.width;
	float refTop = _refRect.top;
	float refBot = _refRect.top + _refRect.height;
	float refLeft = _refRect.left;
	float refRight = _refRect.left + _refRect.width;

	/* If TOP or BOTTOM collisions are possible */
	if ((objLeft <= refLeft && objRight > refLeft)
		|| (objLeft < refRight && objRight >= refRight)
		|| (objLeft >= refLeft && objRight <= refRight))
	{
		if (objTop < refTop && objBot > refTop)
			direction = TOP;
		if (objTop < refBot && objBot > refBot)
			direction = BOTTOM;
	}

	/* If LEFT or RIGHT collisions are possible */
	if ((objTop <= refTop && objBot > refTop)
		|| (objTop < refBot && objBot >= refBot)
		|| (objTop >= refTop && objBot <= refBot))
	{
		/* Collision on LEFT but there may be TOP or BOTTOM as well */
		if (objLeft < refLeft && objRight > refLeft && (objBot - refTop > minGap || objRight - refLeft > minGap))
		{
			if (direction == TOP && objBot - refTop < objRight - refLeft)
				direction = TOP;
			else if (direction == BOTTOM && refBot - objTop < objRight - refLeft)
				direction = BOTTOM;
			else
				direction = LEFT;
		}

		/* Collision on RIGHT but there may be TOP or BOTTOM as well */
		if (objLeft < refRight && objRight > refRight && (objBot - refTop > minGap || refRight - objLeft > minGap))
		{
			if (direction == TOP && objBot - refTop < refRight - objLeft)
				direction = TOP;
			else if (direction == BOTTOM && refBot - objTop < refRight - objLeft)
				direction = BOTTOM;
			else
				direction = RIGHT;
		}
	}

	return direction;
}

void CollisionHandler::ReactToCollision(DisplayableObject& _obj, sf::FloatRect _refRect, CollisionDirection _direction)
{
	sf::FloatRect objRect = _obj.GetCoordinates();
	switch (_direction)
	{
		case TOP:
			objRect.top -= (objRect.top + objRect.height - _refRect.top);
			break;
		case BOTTOM:
			objRect.top += (_refRect.top + _refRect.height - objRect.top);
			break;
		case LEFT:
			objRect.left -= (objRect.left + objRect.width - _refRect.left);
			break;
		case RIGHT:
			objRect.left += (_refRect.left + _refRect.width - objRect.left);
			break;
		case NO_COL:
		default:
			break;
	}
	m_gameEngine->UpdateForegroundItem(_obj.GetID(), objRect);
}
