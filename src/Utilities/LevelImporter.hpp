#ifndef LEVELIMPORTER_H
#define LEVELIMPORTER_H

#include <string>
#include "../irrXML/irrXML.h"
#include "../Items/Pipe.hpp"
#include "Util.hpp"
#include "../EventEngine/EventEngine.hpp"

class GameEngine;

/*
 * LevelImporter: All operations dealing with the XML file representing a level
*/

class LevelImporter
{
	public:
		LevelImporter(EventEngine *_eventEngine);

		bool LoadLevel(std::string _lvlName);
		void StoreCharactersInitialPositions();
		void StoreListForegroundTileNames();
		void StoreBox();
		void StorePipe();
		PipeType GetPipeTypeFromXML();
		void StoreFloor();

	private:
		EventEngine *m_eventEngine;
		irr::io::IrrXMLReader *m_lvlFile;

		std::vector<int> m_pipeIds; // This is used to check that no 2 pipes have the same ID

		std::string GetAttributeValue(const char* _name, bool _optionalAttribute = false);
		float GetAttributeValueAsFloat(const char* _name);
		int GetAttributeValueAsInt(const char* _name);
		void GetCoordinatesAndTileName(sf::Vector2f *_coords, std::string *_tileName);

		static const std::string levelsPath;
};

#endif
