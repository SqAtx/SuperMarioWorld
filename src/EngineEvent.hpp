#include <SFML/Graphics.hpp>
#include "MovingObject.hpp"

typedef enum
{
#ifdef DEBUG_MODE
	INFO_DEBUG,
#endif
	LEVEL_START,
	GAME_STOPPED,
	KEY_PRESSED,
	KEY_RELEASED,
	INFO_POS,
	PLAY_SOUND,
} EventType;

typedef enum
{
	JUMP_SND,
	COIN_SND,
	DEATH_SND
} SoundType;

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
			SoundType m_sound;
		} data;
		std::string m_string; // A string can't be inside a union

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

		void set(EventType _type, SoundType _sound)
		{
			m_type = _type;
			data.m_sound = _sound;
		}

		void set(EventType _type, std::string _str)
		{
			m_type = _type;
			m_string = _str;
		}

#ifdef DEBUG_MODE
		void set(EventType _type, DebugInfo _info)
		{
			m_type = _type;
			m_debugInfo = _info;
		}
#endif
};