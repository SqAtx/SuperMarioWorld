#ifndef BOX_H
#define BOX_H

#include "../DisplayableObject.hpp"

/*
*	Represents a box that the player can hit.
*/
class Box : public DisplayableObject
{
	public:
		Box(std::string _name, sf::Vector2f _coord, State _state);
		Box(std::string _name, float _x, float _y, State _state);
		void Box::Init();

		virtual void UpdateAfterCollision(CollisionDirection _direction, ObjectClass _classOfOtherObject);
};

#endif
