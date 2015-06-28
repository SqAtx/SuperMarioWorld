/*
Level.cpp: All operations dealing with the XML file representing a level
*/

#include "GameEngine.hpp"

using namespace irr;
using namespace io;

const std::string GameEngine::levelsPath = "../assets/levels/";

bool GameEngine::LoadLevel(std::string _lvlName)
{
	bool fileNotEmpty = false;
	std::string lvlFullName = GameEngine::levelsPath + _lvlName + ".xml";
	m_lvlFile = createIrrXMLReader(lvlFullName.c_str());

	while (m_lvlFile && m_lvlFile->read())
	{
		fileNotEmpty = true;
		switch (m_lvlFile->getNodeType())
		{
			case EXN_ELEMENT:
				if (!strcmp("level", m_lvlFile->getNodeName()))
				{
					LevelInfo info;
					info.backgroundName = GetAttributeValue("background");

					EngineEvent tmpEvent(INFO_LVL, info);
					m_engines["gfx"]->PushEvent(tmpEvent);
				}
				if (!strcmp("characters", m_lvlFile->getNodeName()))
					StoreCharactersInitialPositions();
				if (!strcmp("foreground", m_lvlFile->getNodeName()))
					StoreListForegroundTileNames();
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

	delete m_lvlFile;
	m_lvlFile = NULL;
	return true;
}

void GameEngine::StoreCharactersInitialPositions()
{
	sf::Vector2f tmpCoords;
	InfoForDisplay tmpDisplayInfo;
	bool foundOneCharacter = false;
	const char* nodeName;

	while (m_lvlFile && m_lvlFile->read())
	{
		switch (m_lvlFile->getNodeType())
		{
		case EXN_ELEMENT:
			foundOneCharacter = true;
			nodeName = m_lvlFile->getNodeName();
			if (!strcmp("mario", nodeName))
			{
				m_initPosMario.x = GetAttributeValueAsFloat("x");
				m_initPosMario.y = GetAttributeValueAsFloat("y");

				Player *mario = new Player("mario", m_initPosMario);
				m_indexMario = AddCharacterToArray(mario);
				m_listForegroundItems[mario->GetID()] = mario;
			}
			if (!strcmp("goomba", nodeName))
			{
				Direction tmpDir = GetAttributeValue("direction", true) == "left" ? DLEFT : DRIGHT; // direction = right if attribute not here
				Goomba *goomba = new Goomba("goomba", GetAttributeValueAsFloat("x"), GetAttributeValueAsFloat("y"), DLEFT);
				AddCharacterToArray(goomba);
				m_listForegroundItems[goomba->GetID()] = goomba;
			}
			break;
		case EXN_ELEMENT_END:
			if (!foundOneCharacter)
				std::cerr << "No character in level file." << std::endl;
			return;
		default:
			break;
		}
	}
}

void GameEngine::StoreListForegroundTileNames()
{
	bool foundTiles = false;
	const char* nodeName;

	while (m_lvlFile && m_lvlFile->read())
	{
		switch (m_lvlFile->getNodeType())
		{
			case EXN_ELEMENT:
				foundTiles = true;
				nodeName = m_lvlFile->getNodeName();
				if (!strcmp("box", nodeName))
					StoreBox();				
				if (!strcmp("pipe", nodeName))
					StorePipe();
				if (!strcmp("floor_tile", nodeName))
					StoreFloor();
				break;
			case EXN_ELEMENT_END:
				if (!foundTiles)
					std::cerr << "No foreground items in level file." << std::endl;
				return;
			default:
				break;
		}
	}
}

void GameEngine::StoreBox()
{
	sf::Vector2f tmpCoords;
	std::string tmpTileName;
	GetCoordinatesAndTileName(&tmpCoords, &tmpTileName);

	State tmpState = GetAttributeValue("state", true) == "empty" ? EMPTY : NORMAL;

	Box *tmpBox = new Box("item_" + tmpTileName, tmpCoords, tmpState);
	m_listForegroundItems[tmpBox->GetID()] = tmpBox;

	SendInfoPosLvlToGFX(tmpBox->GetInfoForDisplay());
}

void GameEngine::StorePipe()
{
	sf::Vector2f tmpCoords;
	std::string tmpTileName;
	GetCoordinatesAndTileName(&tmpCoords, &tmpTileName);

	PipeType type = GetPipeTypeFromXML();

	Pipe *tmpPipe = new Pipe("item_" + tmpTileName, tmpCoords, NORMAL);
	m_listForegroundItems[tmpPipe->GetID()] = tmpPipe;

	SendInfoPosLvlToGFX(tmpPipe->GetInfoForDisplay());
}

PipeType GameEngine::GetPipeTypeFromXML()
{
	return SPAWN;
}


void GameEngine::StoreFloor()
{
	sf::Vector2f tmpCoords;
	std::string tmpTileName;
	GetCoordinatesAndTileName(&tmpCoords, &tmpTileName);

	DisplayableObject *tmpFloor = new DisplayableObject("floor_" + tmpTileName, tmpCoords, NORMAL);
	m_listForegroundItems[tmpFloor->GetID()] = tmpFloor;

	SendInfoPosLvlToGFX(tmpFloor->GetInfoForDisplay());
}

std::string GameEngine::GetAttributeValue(const char* _name, bool _optionalAttribute)
{
	std::string str(m_lvlFile->getAttributeValueSafe(_name));
	if (str == "" && !_optionalAttribute)
		std::cerr << "Can't read attribute " << _name << std::endl;
	return str;
}

float GameEngine::GetAttributeValueAsFloat(const char* _name)
{
	float ret = m_lvlFile->getAttributeValueAsFloat(_name);
	if (ret == -1)
		std::cerr << "Can't read attribute " << _name << std::endl;
	return ret;
}

void GameEngine::SendInfoPosLvlToGFX(InfoForDisplay _info)
{
	EngineEvent tmpEvent(INFO_POS_LVL, _info);
	m_engines["gfx"]->PushEvent(tmpEvent);
}

void GameEngine::GetCoordinatesAndTileName(sf::Vector2f *_coords, std::string *_tileName)
{
	_coords->x = GetAttributeValueAsFloat("x");
	_coords->y = GetAttributeValueAsFloat("y");

	*_tileName = GetAttributeValue("sprite");
}