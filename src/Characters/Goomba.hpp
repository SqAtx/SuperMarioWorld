#ifndef GOOMBA_H
#define GOOMBA_H

#include "Enemy.hpp"

class Goomba : public Enemy
{
	public:
		Goomba(EventEngine *_eventEngine, std::string _name, sf::Vector2f _coord, Direction _dir);
		Goomba(EventEngine *_eventEngine, std::string _name, float _x, float _y, Direction _dir);

		virtual float GetMaxAbsVelocity_X();

		virtual void UpdateAfterCollision(CollisionDirection _dir, ObjectClass _classOfOtherObject);

	protected:

		virtual void AddOwnAcceleration();
};

#endif
