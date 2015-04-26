#include <SFML/Graphics.hpp>
#include "MovingObject.hpp"

typedef enum
{
#ifdef DEBUG_MODE
	INFO_DEBUG,
#endif
	GAME_STOPPED,
	KEY_PRESSED,
	KEY_RELEASED,
	INFO_POS,
} EventType;

/* This class represents a message sent from an engine to another */
class EngineEvent
{
	public:

		EventType m_type;
		
		union
		{
			sf::Keyboard::Key m_key;
			struct { // Unnamed struct to fool VS which is being annoying..
				InfoForDisplay m_infoDisplay;
			};
		} data;

#ifdef DEBUG_MODE
		DebugInfo m_debugInfo;
#endif

		void set(EventType _type)
		{
			m_type = _type;
			data.m_key = sf::Keyboard::Unknown;
		}

		void set(EventType _type, sf::Keyboard::Key _key)
		{
			m_type = _type;
			data.m_key = _key;
		}

		void set(EventType _type, InfoForDisplay _info)
		{
			m_type = _type;
			data.m_infoDisplay = _info;
		}

#ifdef DEBUG_MODE
		void set(EventType _type, DebugInfo _info)
		{
			m_type = _type;
			m_debugInfo = _info;
		}
#endif
};