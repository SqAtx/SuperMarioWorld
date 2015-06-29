#ifndef DISPLAYABLEOBJECT_H
#define DISPLAYABLEOBJECT_H

#include <SFML/System/Vector2.hpp>
#include "Utilities/Debug.hpp"
#include "Utilities/PhysicsConstants.hpp"

/*
*	Information sent from g to gfx for display. The name and state will be used to fetch the correct sprite.
*/
struct InfoForDisplay
{
	unsigned int id;
	std::string name;	// to find sprite
	std::string currentSprite;
	State state;		// Idem
	sf::FloatRect coordinates;
	bool reverse; // Reverse sprite display (left/right) ?
};

/*
*	A DisplayableObject can be the player itself, an enemy, or stuff like pipes, '?' blocks, the floor etc. Anything you can display.
*/
class DisplayableObject
{
	public:
		DisplayableObject();
		DisplayableObject(std::string _name, sf::Vector2f _coord, State _state = UNKNOWN);
		DisplayableObject(std::string _name, float _x, float _y, State _state = UNKNOWN);
		virtual ~DisplayableObject();

		virtual InfoForDisplay GetInfoForDisplay();
		virtual void UpdateAfterCollision(CollisionDirection _direction, ObjectClass _classOfOtherObject);

		sf::FloatRect GetCoordinates() const;
		void SetCoordinates(const sf::FloatRect _coord);
		sf::Vector2f GetPosition() const { return m_coord; };
		void SetPosition(const sf::Vector2f _pos) { m_coord = _pos; };
		ObjectClass GetClass() const { return m_class; };
		State GetState() const { return m_state; };
		unsigned int GetID() const { return m_id; };
		void SetX(const float _x) { m_coord.x = _x; };
		void SetY(const float _y) { m_coord.y = _y; };

	protected:
		int m_id; // Unique identifier for each object
		std::string m_name;
		ObjectClass m_class;
		State m_state;

		sf::Vector2f m_coord; // Origin: the top left corner, with respect to the top left corner of the window
		sf::Vector2f m_size;

		bool m_reverseSprite;

	private:
		static unsigned int id;
};

#endif
