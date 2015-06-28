#ifndef ENEMY_H
#define ENEMY_H

#include "MovingObject.hpp"

class Enemy : public MovingObject
{
	public:
		Enemy(std::string _name, sf::Vector2f _coord, Direction _dir);
		Enemy(std::string _name, float _x, float _y, Direction _dir);
		void Enemy::Init();

		virtual float GetMaxAbsVelocity_X() = 0;
		virtual void Move(Instruction _inst);

		InfoForDisplay GetInfoForDisplay();
		virtual void UpdateAfterCollision(CollisionDirection _dir, ObjectClass _classOfOtherObject) = 0;
		void UpdateAfterCollisionWithMapEdge(CollisionDirection _dir, float _gap);

	protected:

		virtual void AddOwnAcceleration() = 0;
};

#endif