/*
*	Util class: Contains all the methods that can be used anywhere
*/

#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <vector>
#include <SFML/System.hpp>
#include <SFML\Graphics.hpp>

class DisplayableObject;
struct InfoForDisplay;

typedef enum {
	UNKNOWN,
	STATIC,
	WALK,
	RUN,
	JUMP,		// Only used for transmission to GameEngine
	FALL,		// Idem
	NORMAL,		// Items with only one state e.g. the animated foreground items
	EMPTY		// ? Boxes
} State;

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

class Util
{
	public:
		static bool isInteger(std::string& _str);
		static std::vector<std::string> Split(std::string _str, char _sep);
		static bool Util::StringEndsWith(std::string _full, std::string _ending);
};

class CompareInfoForDisplay {
	public:
		bool operator()(InfoForDisplay const& _a, InfoForDisplay const& _b);
};

#endif