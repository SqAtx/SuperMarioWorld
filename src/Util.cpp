#include "Util.hpp"

bool Util::isInteger(std::string& _str)
{
	char *end;
	long i = std::strtol(_str.c_str(), &end, 10);
	return (i != 0 && *end == '\0') || (i == 0 && _str.c_str() != end); // Conversion OK with no trailing letters after the number OR number is 0 and conversion actually happenned
}

std::vector<std::string> Util::Split(std::string _str, char _sep)
{
	std::vector<std::string> splitted;
	const char* cstr = _str.c_str();
	char cur;
	int i = 0;

	std::string buf = "";
	do
	{
		cur = cstr[i];
		if (cur == _sep || cur == '\0')
		{
			if (buf != "")
			{
				splitted.push_back(buf);
				buf = "";
			}
		}
		else
			buf += cur;

		i++;
	} while (cur != '\0');

	return splitted;
}

bool CompareVector2f::operator()(sf::Vector2f const& _a, sf::Vector2f const& _b)
{
	if (_a.x < _b.x)
		return true;
	if (_a.x == _b.x && _a.y < _b.y)
		return true;
	return false;
}
