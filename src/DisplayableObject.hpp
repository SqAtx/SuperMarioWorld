#ifndef DISPLAYABLEOBJECT_H
#define DISPLAYABLEOBJECT_H

#include <SFML/System/Vector2.hpp>
#include "Debug.hpp"
#include "PhysicsConstants.hpp"

typedef enum {
	STATIC,
	WALK,
	RUN,
	JUMP,	// Only used for transmission to GameEngine
	FALL,	// Idem
	UNKNOWN
} State;

/*
*	Information sent from g to gfx for display. The name and state will be used to fetch the correct sprite.
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
*	A DisplayableObject can be the player itself, an enemy, or stuff like pipes, '?' blocks, the floor etc. Anything you can display.
*/
class DisplayableObject
{
	public:
		DisplayableObject(std::string _name, sf::Vector2f _coord);
		DisplayableObject(std::string _name, float _x, float _y);
		virtual ~DisplayableObject();

		virtual InfoForDisplay GetInfoForDisplay();
		sf::Vector2f GetPosition() const { return m_coord; };
		unsigned int GetID() { return m_id; };
		void SetX(float _x) { m_coord.x = _x; };
		void SetY(float _y) { m_coord.y = _y; };

	protected:
		int m_id; // Unique identifier for each object
		std::string m_name;
		State m_state;

		sf::Vector2f m_coord; // Coordinates of the top left corner, in pixels, with respect to the top left corner of the window

		bool m_reverseSprite;

	private:
		static unsigned int id;
};

#endif
