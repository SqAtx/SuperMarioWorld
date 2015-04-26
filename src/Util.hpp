/*
*	Util class: Contains all the methods that can be used anywhere
*/

#include <string>
#include <vector>

class Util
{
	public:
		static bool isInteger(std::string& _str);
		static std::vector<std::string> Split(std::string _str, char _sep);
};