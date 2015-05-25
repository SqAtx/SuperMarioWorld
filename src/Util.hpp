/*
*	Util class: Contains all the methods that can be used anywhere
*/

#include <string>
#include <vector>
#include <SFML/System.hpp>

class Util
{
	public:
		static bool isInteger(std::string& _str);
		static std::vector<std::string> Split(std::string _str, char _sep);
};

class CompareVector2f {
	public:
		bool operator()(sf::Vector2f const& _a, sf::Vector2f const& _b);
};