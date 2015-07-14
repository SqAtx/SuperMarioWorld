#include <SFML/Graphics.hpp>
#include "../Characters/MovingObject.hpp"

typedef enum
{
#ifdef DEBUG_MODE
	INFO_DEBUG,
#endif
	LEVEL_START,			// g to s
	GAME_STOPPED,
	KEY_PRESSED,			// gfx to g
	KEY_RELEASED,			// gfx to g
	INFO_POS_CHAR,			// g to gfx during game: character (Mario or enemy) position
	INFO_POS_LVL,			// gfx <-> g: position of a foreground sprite
	INFO_LVL,				// g to gfx when loading level: basing info about level
	PLAY_SOUND,
	DEATH_SOUND_STARTED,	// s to g
	DEATH_SOUND_STOPPED		// s to g
} EventType;

typedef enum
{
	JUMP_SND,
	COIN_SND,
	DEATH_SND
} SoundType;

struct LevelInfo
{
	std::string name;
	std::string backgroundName;
	sf::Vector2f size;
};

/* This class represents a message sent from an engine to another */
class EngineEvent
{
	public:

		EventType m_type;

		struct { // Unnamed struct to fool VS which is being annoying..
			union {
				sf::Keyboard::Key m_key;
				SoundType m_sound;
				int m_id;
			};
			InfoForDisplay m_infoDisplay;
		} data;
		std::string m_string; // A string can't be inside a union
		sf::FloatRect m_rect;
		LevelInfo m_levelInfo;

#ifdef DEBUG_MODE
		DebugInfo m_debugInfo;
#endif

		EngineEvent()
		{

		}

		EngineEvent(EventType _type)
		{
			set(_type);
		}
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

		EngineEvent(EventType _type, InfoForDisplay _info)
		{
			set(_type, _info);
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

		EngineEvent(EventType _type, int _id, sf::FloatRect _rect = sf::FloatRect())
		{
			set(_type, _id, _rect);
		}

		void set(EventType _type, int _id, sf::FloatRect _rect = sf::FloatRect())
		{
			m_type = _type;
			data.m_id = _id;
			m_rect = _rect;
		}

		EngineEvent(EventType _type, LevelInfo _info)
		{
			set(_type, _info);
		}
		void set(EventType _type, LevelInfo _info)
		{
			m_type = _type;
			m_levelInfo = _info;
		}

#ifdef DEBUG_MODE
		EngineEvent(EventType _type, DebugInfo _info)
		{
			set(_type, _info);
		}
		void set(EventType _type, DebugInfo _info)
		{
			m_type = _type;
			m_debugInfo = _info;
		}
#endif
};
