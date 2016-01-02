#include "KeyboardEvent.hpp"

KeyboardEvent::KeyboardEvent(sf::Event _sfEvent)
{
	m_type = _sfEvent.type; 
	m_key = _sfEvent.key.code; 
}

sf::Event::EventType KeyboardEvent::GetType()
{
	return m_type;
}
sf::Keyboard::Key KeyboardEvent::GetKey()
{
	return m_key;
}
