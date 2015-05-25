/*
*	Util class: Contains all the methods that can be used anywhere
*/

#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <vector>
#include <SFML/System.hpp>

class DisplayableObject;

class Util
{
	public:
		static bool isInteger(std::string& _str);
		static std::vector<std::string> Split(std::string _str, char _sep);
};

class CompareDisplayableObjects {
	public:
		bool operator()(DisplayableObject const& _a, DisplayableObject const& _b);
};

#endif