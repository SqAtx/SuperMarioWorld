#include "Box.hpp"

Box::Box(std::string _name, sf::Vector2f _coord, State _state) : DisplayableObject(_name, _coord, _state)
{
	Init();
}

Box::Box(std::string _name, float _x, float _y, State _state) : DisplayableObject(_name, _x, _y, _state)
{
	Init();
}

void Box::Init()
{
	m_class = LEVEL_BLOCK; // Is probably to change to HARMLESS_OBJECT at some point
}

void Box::UpdateAfterCollision(CollisionDirection _direction, ObjectClass _classOfOtherObject)
{
	if (_direction == BOTTOM && _classOfOtherObject == PLAYER)
	{
		m_state = EMPTY;
	}
}
