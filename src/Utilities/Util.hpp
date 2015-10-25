/*
*	Util class: Contains all the methods that can be used anywhere
*/

#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <vector>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class DisplayableObject;
struct InfoForDisplay;

enum ObjectClass
{
	PLAYER,
	ENEMY,
	HARMLESS_OBJECT, // Just an idea for blocs that can move and push / be pushed by characters (player and enemies), as opposed to a level block that doesn't move
	LEVEL_BLOCK
};

enum State 
{
	UNKNOWN,
	STATIC,
	WALK,
	RUN,
	JUMP,		// Only used for transmission to GameEngine
	FALL,		// Idem
	NORMAL,		// Items with only one state e.g. the animated foreground items
	EMPTY		// ? Boxes
};

enum Direction 
{
	DLEFT,
	DRIGHT
};

enum Instruction // From user to player
{
	GO_LEFT,
	GO_RIGHT,
	STOP_LEFT,
	STOP_RIGHT
};

enum JumpState
{
	JUMPING,
	REACHINGAPEX, // Phase between the jump and the fall: the object is still rising but without acceleration on the Y axis
	FALLING,
	ONFLOOR,
	NONE	// At the beginning of the level, for example
};

enum CollisionDirection 
{
	TOP,
	BOTTOM,
	LEFT,
	RIGHT,
	NO_COL
};

enum PipeType
{
	TRAVEL,		// Mario can travel through the pipe
	SPAWN,		// The pipe is used to spawn enemies
	FLOWER		// Flower in a pipe, classic enemy
};

enum SoundType
{
	JUMP_SND,
	COIN_SND,
	DEATH_SND,
	KICK_SND
};


namespace Sprite
{
	/* To decide whether we keep the current sprite and avoid calling GetTextureNameFromDisplayInfo */
	typedef enum {
		STATIC,			// Yes
		ANIMATED,		// No
		NEW_STATIC,		// No: is static BUT different than the previous state (used to be NEW_STATE)
		UNKNOWN
	} StaticOrAnimated;
}

#ifdef DEBUG_MODE
namespace Debug
{
	static const std::string StateStrings[] = { "UNKNOWN", "STATIC", "WALK", "RUN", "JUMP", "FALL", "NORMAL", "EMPTY" };
	static const std::string GetTextForState(int _stateValue)
	{
		return StateStrings[_stateValue];
	}

	static const std::string JumpStateStrings[] = { "JUMPING", "REACHINGAPEX", "FALLING", "ONFLOOR", "NONE" };
	static const std::string GetTextForJumpState(int _jumpStateValue)
	{
		return JumpStateStrings[_jumpStateValue];
	}
}

struct DebugInfo {
	sf::Vector2f velocity;
	sf::Vector2f acceleration;
	State state;
	JumpState jumpState;
};
#endif

class Util
{
	public:
		static bool isInteger(std::string& _str);
		static std::vector<std::string> Split(std::string _str, char _sep);
		static bool StringEndsWith(std::string _full, std::string _ending);
		static CollisionDirection OppositeCollisionDirection(CollisionDirection _dir);
};

class CompareInfoForDisplay {
	public:
		bool operator()(InfoForDisplay const& _a, InfoForDisplay const& _b);
};

#endif
