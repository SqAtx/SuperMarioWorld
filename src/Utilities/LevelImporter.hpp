#ifndef LEVELIMPORTER_H
#define LEVELIMPORTER_H

#include <string>
#include "../irrXML/irrXML.h"
#include "../Items/Pipe.hpp"
#include "Util.hpp"

class GameEngine;

/*
 * LevelImporter: All operations dealing with the XML file representing a level
*/

class LevelImporter
{
	public:
		LevelImporter(GameEngine *_parent);

		bool LoadLevel(std::string _lvlName);
		void StoreCharactersInitialPositions();
		void StoreListForegroundTileNames();
		void StoreBox();
		void StorePipe();
		PipeType GetPipeTypeFromXML();
		void StoreFloor();

	private:
		GameEngine *m_gameEngine;
		irr::io::IrrXMLReader *m_lvlFile;

		std::string GetAttributeValue(const char* _name, bool _optionalAttribute = false);
		float GetAttributeValueAsFloat(const char* _name);
		int GetAttributeValueAsInt(const char* _name);
		void SendInfoPosLvlToGFX(InfoForDisplay _info);
		void GetCoordinatesAndTileName(sf::Vector2f *_coords, std::string *_tileName);

		static const std::string levelsPath;
};

#endif
