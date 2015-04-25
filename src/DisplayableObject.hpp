#ifndef DISPLAYABLEOBJECT_H
#define DISPLAYABLEOBJECT_H

#include <string>
#include <SFML/System/Vector2.hpp>
#include "Debug.hpp"
#include "PhysicsConstants.hpp"

typedef enum {
	STATIC,
	WALK,
	RUN,
	UNKNOWN
} State;

/*
*	Information sent from g to gfx for display. The name will be used to fetch the sprite(s).
*/
struct InfoForDisplay
{
	unsigned int id;
	std::string name;	// to find sprite
	State state;		// Idem
	sf::Vector2f coordinates;
	bool reverse; // Reverse sprite display (left/right) ?
};

/*
*	A DisplayableObject can be the player itself, an enemy, or stuff like pipes, '?' blocks, etc.
*/
class DisplayableObject
{
	public:
		DisplayableObject(std::string _name, sf::Vector2f _coord);
		DisplayableObject(std::string _name, float _x, float _y);
		virtual ~DisplayableObject();

		virtual InfoForDisplay GetInfoForDisplay();

#ifdef DEBUG_MODE
		sf::Vector2f GetPosition() { return m_coord; };
#endif

	protected:
		int m_id; // Unique identifier for each object
		std::string m_name;
		State m_state;

		sf::Vector2f m_coord; // Coordinates of the bottom left corner, in pixels, with respect to the top left corner of the window

		bool m_reverseSprite;

	private:
		static unsigned int id;
};

#endif
