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

/* After refactoring, this is useless now.. I leave it "in case" until I get tired of it */
bool Util::StringEndsWith(std::string _full, std::string _ending)
{
	if (_ending == "")
		return true;
	int lenDiff = _full.length() - _ending.length();
	if (lenDiff < 0)
		return false;

	return !_full.compare(lenDiff, _ending.length(), _ending);
}

bool CompareInfoForDisplay::operator()(InfoForDisplay const& _a, InfoForDisplay const& _b)
{
	return (_a.id < _b.id);
}


