#ifndef EVENT_H
#define EVENT_H

#include "../Utilities/Util.hpp"

class MovingObject;

/**
 * Base class of events
 * @author Nicolas Djambazian <nicolas@djambazian.fr>
 */
class Event
{
	public:
		Event() { };
		Event(std::string _stringInfo) { m_stringInfo = _stringInfo; };
		Event(LevelInfo _levelInfo) { m_levelInfo = _levelInfo; };
		Event(MovingObject *_movingObject) { m_movingObject = _movingObject; };

		std::string GetString() { return m_stringInfo; };
		void SetString(std::string _value) { m_stringInfo = _value; };

		LevelInfo GetLevelInfo() { return m_levelInfo; };
		void SetLevelInfo(LevelInfo _value) { m_levelInfo = _value; };

		MovingObject* GetMovingObject() { return m_movingObject; };
		void SetMovingObject(MovingObject *_value) { m_movingObject = _value; };

	private:
		std::string m_stringInfo;
		LevelInfo m_levelInfo;
		MovingObject *m_movingObject;
};

#endif // EVENT_H
