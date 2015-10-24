#ifndef EVENT_H
#define EVENT_H

#include <string>

/**
 * Base class of events
 * @author Nicolas Djambazian <nicolas@djambazian.fr>
 */
class Event
{
	public:
		Event() { };
		Event(std::string _stringInfo) { m_stringInfo = _stringInfo; };

		std::string GetString() { return m_stringInfo; };
		void SetString(std::string _value) { m_stringInfo = _value; };

	private:
		std::string m_stringInfo;
};

#endif // EVENT_H
