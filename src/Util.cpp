#include "Util.hpp"
#include "DisplayableObject.hpp"

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

bool CompareDisplayableObjects::operator()(DisplayableObject const& _a, DisplayableObject const& _b)
{
	if (_a.GetPosition().x < _b.GetPosition().x)
		return true;
	if (_a.GetPosition().x == _b.GetPosition().x && _a.GetPosition().y < _b.GetPosition().y)
		return true;
	return false;
}
