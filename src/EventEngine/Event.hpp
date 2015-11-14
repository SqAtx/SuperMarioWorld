#ifndef EVENT_H
#define EVENT_H

#include "../Utilities/Util.hpp"

class MovingObject;
class Pipe;

#ifdef DEBUG_MODE
struct DebugInfo;
#endif

/**
 * Base class of events
 * @author Nicolas Djambazian <nicolas@djambazian.fr>
 */
class Event
{
	public:
		Event() { };
		Event(unsigned int _id) { m_id = _id; };
		Event(std::string _stringInfo) { m_stringInfo = _stringInfo; };
		Event(LevelInfo *_levelInfo) { m_levelInfo = _levelInfo; };
		Event(MovingObject *_movingObject) { m_movingObject = _movingObject; };
		Event(DisplayableObject *_displayableObject) { m_displayableObject = _displayableObject; };
		Event(Pipe *_pipe) { m_pipe = _pipe; };
		Event(InfoForDisplay *_infoForDisplay) { m_infoForDisplay = _infoForDisplay; };
#ifdef DEBUG_MODE
		Event(DebugInfo *_debugInfo) { m_debugInfo = _debugInfo; };
#endif

		std::string GetString() { return m_stringInfo; };
		unsigned int GetID() { return m_id; };
		LevelInfo* GetLevelInfo() { return m_levelInfo; };
		MovingObject* GetMovingObject() { return m_movingObject; };
		DisplayableObject* GetDisplayableObject() { return m_displayableObject; };
		Pipe* GetPipe() { return m_pipe; };
		InfoForDisplay* GetInfoForDisplay() { return m_infoForDisplay; };
#ifdef DEBUG_MODE
		DebugInfo* GetDebugInfo() { return m_debugInfo; };
#endif

		void SetString(std::string _value) { m_stringInfo = _value; };

	private:
		unsigned int m_id;
		std::string m_stringInfo;
		LevelInfo *m_levelInfo;
		MovingObject *m_movingObject;
		DisplayableObject *m_displayableObject;
		Pipe *m_pipe;
		InfoForDisplay *m_infoForDisplay;
#ifdef DEBUG_MODE
		DebugInfo *m_debugInfo;
#endif
};

#endif // EVENT_H
