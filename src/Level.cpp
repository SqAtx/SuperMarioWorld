/*
Level.cpp: All operations dealing with the XML file representing a level
*/

#include "GraphicsEngine.hpp"

using namespace irr;
using namespace io;

const std::string GraphicsEngine::levelsPath = "../assets/levels/";

bool GraphicsEngine::LoadLevel(std::string _lvlName)
{
	bool fileNotEmpty = false;
	std::string lvlFullName = GraphicsEngine::levelsPath + _lvlName + ".xml";
	IrrXMLReader* lvlFile = createIrrXMLReader(lvlFullName.c_str());

	while (lvlFile && lvlFile->read())
	{
		fileNotEmpty = true;
		switch (lvlFile->getNodeType())
		{
			case EXN_ELEMENT:
				if (!strcmp("level", lvlFile->getNodeName()))
					m_currentBackgroundName = GetAttributeValue(lvlFile, "background");
				if (!strcmp("floor", lvlFile->getNodeName()))
					FillListFloorTileNames(lvlFile);
				break;
			default:
				break;
		}
	}

	if (!fileNotEmpty)
	{
		std::cerr << "Can't read level file " << lvlFullName << std::endl;
		return false;
	}

	delete lvlFile;
	return true;
}

void GraphicsEngine::FillListFloorTileNames(irr::io::IrrXMLReader *_lvlFile)
{
	sf::Vector2f tmpCoords;
	std::string tmpTileName;
	bool foundTiles = false;

	while (_lvlFile && _lvlFile->read())
	{
		switch (_lvlFile->getNodeType())
		{
			case EXN_ELEMENT:
				foundTiles = true;
				if (!strcmp("tile", _lvlFile->getNodeName()))
				{
					tmpCoords.x = GetAttributeValueAsFloat(_lvlFile, "x");
					tmpCoords.y = GetAttributeValueAsFloat(_lvlFile, "y");
					tmpTileName = GetAttributeValue(_lvlFile, "type");
					m_listFloorTileNames[tmpCoords] = tmpTileName;
				}
				break;
			case EXN_ELEMENT_END:
				if (!foundTiles)
					std::cerr << "No floor tiles in level file." << std::endl;
				return;
			default:
				break;
		}
	}
}

std::string GraphicsEngine::GetAttributeValue(IrrXMLReader *_lvlFile, const char* _name)
{
	std::string str(_lvlFile->getAttributeValueSafe(_name));
	if (str == "")
		std::cerr << "Can't read attribute " << _name << std::endl;
	return str;
}

float GraphicsEngine::GetAttributeValueAsFloat(IrrXMLReader *_lvlFile, const char* _name)
{
	float ret = _lvlFile->getAttributeValueAsFloat(_name);
	if (ret == -1)
		std::cerr << "Can't read attribute " << _name << std::endl;
	return ret;
}