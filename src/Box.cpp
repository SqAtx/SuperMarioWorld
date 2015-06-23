#include "Box.hpp"

Box::Box(std::string _name, sf::Vector2f _coord, State _state) : DisplayableObject(_name, _coord, _state)
{

}

Box::Box(std::string _name, float _x, float _y, State _state) : DisplayableObject(_name, _x, _y, _state)
{

}

void Box::ReceiveHit(CollisionDirection _direction)
{
	if (_direction == BOTTOM)
	{
		m_state = EMPTY;
	}
}