#include "DisplayableObject.hpp"

unsigned int DisplayableObject::id = 1;

// Needed in order to create maps of displayable objects
DisplayableObject::DisplayableObject()
{
	m_id = 0;
}

DisplayableObject::DisplayableObject(std::string _name, sf::Vector2f _coord, State _state) : DisplayableObject(_name, _coord.x, _coord.y, _state)
{

}

DisplayableObject::DisplayableObject(std::string _name, float _x, float _y, State _state)
{
	m_id = DisplayableObject::id;
	DisplayableObject::id++;

	m_name = _name;
	m_coord.x = _x;
	m_coord.y = _y;

	m_state = _state;
}

DisplayableObject::~DisplayableObject()
{

}

InfoForDisplay DisplayableObject::GetInfoForDisplay()
{
	InfoForDisplay info;
	info.id = m_id;
	info.name = m_name;
	info.state = m_state;
	info.coordinates = GetCoordinates();
	info.reverse = m_reverseSprite;
	return info;
}

sf::FloatRect DisplayableObject::GetCoordinates() const
{
	sf::FloatRect coords(m_coord.x, m_coord.y, m_size.x, m_size.y);
	return coords;
}

void DisplayableObject::SetCoordinates(const sf::FloatRect _coord)
{
	m_coord.x = _coord.left;
	m_coord.y = _coord.top;
	m_size.x = _coord.width;
	m_size.y = _coord.height;
}
