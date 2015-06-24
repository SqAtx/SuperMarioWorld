/*
Level.cpp: All operations dealing with the XML file representing a level
*/

#include "GameEngine.hpp"

using namespace irr;
using namespace io;

const std::string GameEngine::levelsPath = "../assets/levels/";

bool GameEngine::LoadLevel(std::string _lvlName)
{
	EngineEvent tmpEvent;
	bool fileNotEmpty = false;
	std::string lvlFullName = GameEngine::levelsPath + _lvlName + ".xml";
	IrrXMLReader* lvlFile = createIrrXMLReader(lvlFullName.c_str());

	while (lvlFile && lvlFile->read())
	{
		fileNotEmpty = true;
		switch (lvlFile->getNodeType())
		{
			case EXN_ELEMENT:
				if (!strcmp("level", lvlFile->getNodeName()))
				{
					LevelInfo info;
					info.backgroundName = GetAttributeValue(lvlFile, "background");
					tmpEvent.set(INFO_LVL, info);
					m_engines["gfx"]->PushEvent(tmpEvent);
				}
				if (!strcmp("characters", lvlFile->getNodeName()))
					StoreCharactersInitialPositions(lvlFile);
				if (!strcmp("foreground", lvlFile->getNodeName()))
					StoreListForegroundTileNames(lvlFile);
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

void GameEngine::StoreCharactersInitialPositions(irr::io::IrrXMLReader *_lvlFile)
{
	sf::Vector2f tmpCoords;
	InfoForDisplay tmpDisplayInfo;
	EngineEvent tmpEvent;
	bool foundOneCharacter = false;

	while (_lvlFile && _lvlFile->read())
	{
		switch (_lvlFile->getNodeType())
		{
		case EXN_ELEMENT:
			foundOneCharacter = true;
			if (!strcmp("mario", _lvlFile->getNodeName()))
			{
				m_initPosMario.x = GetAttributeValueAsFloat(_lvlFile, "x");
				m_initPosMario.y = GetAttributeValueAsFloat(_lvlFile, "y");

				Player *mario = new Player("mario", m_initPosMario);
				m_indexMario = AddCharacterToArray(mario);
				m_listForegroundItems[mario->GetID()] = mario;
			}
			if (!strcmp("goomba", _lvlFile->getNodeName()))
			{
				Direction tmpDir = GetAttributeValue(_lvlFile, "direction", true) == "left" ? DLEFT : DRIGHT; // direction = right if attribute not here
				Goomba *goomba = new Goomba("goomba", GetAttributeValueAsFloat(_lvlFile, "x"), GetAttributeValueAsFloat(_lvlFile, "y"), DLEFT);
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

void GameEngine::StoreListForegroundTileNames(irr::io::IrrXMLReader *_lvlFile)
{
	sf::Vector2f tmpCoords;
	std::string tmpTileName;
	State tmpState;
	EngineEvent tmpEvent;
	InfoForDisplay tmpInfo;
	bool foundTiles = false;

	while (_lvlFile && _lvlFile->read())
	{
		switch (_lvlFile->getNodeType())
		{
			case EXN_ELEMENT:
				foundTiles = true;
				if (!strcmp("box", _lvlFile->getNodeName()))
				{
					tmpCoords.x = GetAttributeValueAsFloat(_lvlFile, "x");
					tmpCoords.y = GetAttributeValueAsFloat(_lvlFile, "y");
					tmpTileName = GetAttributeValue(_lvlFile, "sprite");
					tmpState = GetAttributeValue(_lvlFile, "state", true) == "empty" ? EMPTY : NORMAL;

					Box *tmpBox = new Box("item_" + tmpTileName, tmpCoords, tmpState);
					m_listForegroundItems[tmpBox->GetID()] = tmpBox;

					tmpInfo = tmpBox->GetInfoForDisplay();
					tmpEvent.set(INFO_POS_LVL, tmpInfo);
					m_engines["gfx"]->PushEvent(tmpEvent);
				}
				if (!strcmp("floor_tile", _lvlFile->getNodeName()))
				{
					tmpCoords.x = GetAttributeValueAsFloat(_lvlFile, "x");
					tmpCoords.y = GetAttributeValueAsFloat(_lvlFile, "y");
					tmpTileName = GetAttributeValue(_lvlFile, "sprite");

					DisplayableObject *tmpFloor = new DisplayableObject("floor_" + tmpTileName, tmpCoords, NORMAL);
					m_listForegroundItems[tmpFloor->GetID()] = tmpFloor;

					tmpInfo = tmpFloor->GetInfoForDisplay();
					tmpEvent.set(INFO_POS_LVL, tmpInfo);
					m_engines["gfx"]->PushEvent(tmpEvent);
				}
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

std::string GameEngine::GetAttributeValue(IrrXMLReader *_lvlFile, const char* _name, bool _optionalAttribute)
{
	std::string str(_lvlFile->getAttributeValueSafe(_name));
	if (str == "" && !_optionalAttribute)
		std::cerr << "Can't read attribute " << _name << std::endl;
	return str;
}

float GameEngine::GetAttributeValueAsFloat(IrrXMLReader *_lvlFile, const char* _name)
{
	float ret = _lvlFile->getAttributeValueAsFloat(_name);
	if (ret == -1)
		std::cerr << "Can't read attribute " << _name << std::endl;
	return ret;
}