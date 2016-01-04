#include "DisplayableObject.hpp"
#include "EventEngine/EventEngine.hpp"

unsigned int DisplayableObject::id = 1;

// Needed in order to create maps of displayable objects and temporary variables
DisplayableObject::DisplayableObject()
{
	m_id = 0;
}

DisplayableObject::DisplayableObject(EventEngine *_eventEngine, std::string _name, sf::Vector2f _coord, State _state) : DisplayableObject(_eventEngine, _name, _coord.x, _coord.y, _state)
{

}

DisplayableObject::DisplayableObject(EventEngine *_eventEngine, std::string _name, float _x, float _y, State _state)
{
	m_eventEngine = _eventEngine;

	m_id = DisplayableObject::id;
	DisplayableObject::id++;

	m_name = _name;
	m_coord.x = _x;
	m_coord.y = _y;

	m_class = LEVEL_BLOCK; // May be overwritten by constructors in children
	m_state = _state;

	m_reverseSprite = false;
}

DisplayableObject::~DisplayableObject()
{
	// Don't delete m_eventEngine because it lives longer than the objects..
}

void DisplayableObject::Slide(sf::Vector2f _vec)
{
	Slide(_vec.x, _vec.y);
}

void DisplayableObject::Slide(float _x, float _y)
{
	m_coord.x += _x;
	m_coord.y += _y;
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

void DisplayableObject::UpdateAfterCollision(CollisionDirection _direction, ObjectClass _classOfOtherObject)
{
	/* Virtual. Nothing should happen here. Could be in moving object but some objects such as floor tiles might react to collisions one day */
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
