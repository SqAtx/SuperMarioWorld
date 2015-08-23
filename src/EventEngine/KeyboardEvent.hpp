#ifndef KEYBOARDEVENT_H
#define KEYBOARDEVENT_H

#include "Event.hpp"
#include <SFML/Window/Event.hpp>

/**
* Keyboard events: key pressed or released
* @author Kevin Guillaumond
*/
class KeyboardEvent: public Event
{
	public:
		KeyboardEvent(sf::Event _sfEvent);

		sf::Event::EventType GetType();
		sf::Keyboard::Key GetKey();

	private:
		sf::Event::EventType m_type;
		sf::Keyboard::Key m_key;
};

#endif // KEYBOARDEVENT_H
