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
			{
				if (!strcmp("level", lvlFile->getNodeName()))
					m_currentBackgroundName = GetAttributeValue(lvlFile, "background");
			}
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

std::string GraphicsEngine::GetAttributeValue(IrrXMLReader *_lvlFile, const char* _name)
{
	std::string str(_lvlFile->getAttributeValueSafe(_name));
	if (str == "")
		std::cerr << "Can't read attribute " << _name << std::endl;
	return str;
}