#ifndef COLLISION_HANDLER_H
#define COLLISION_HANDLER_H

#include "../Characters/Player.hpp"

class GameEngine;

/*
 * Collision handler
*/
class CollisionHandler
{
	public:
		CollisionHandler(GameEngine *_parent);
		~CollisionHandler();

		void HandleCollisionsWithMapEdges(MovingObject& _obj);

		CollisionDirection DetectCollisionWithObj(MovingObject& _obj, DisplayableObject& _ref);
		void ReactToCollisionsWithObj(MovingObject& _obj, DisplayableObject& _ref, CollisionDirection _direction);
		void SendNewObjectPositionToGFX(DisplayableObject& _obj);
		CollisionDirection HandleCollisionWithRect(unsigned int _objId, sf::FloatRect _ref);
		CollisionDirection DetectCollisionWithRect(sf::FloatRect _obj, sf::FloatRect _ref);
		void ReactToCollision(DisplayableObject& _obj, sf::FloatRect _refRect, CollisionDirection _direction);

	private:
		GameEngine *m_gameEngine;
};
#endif
