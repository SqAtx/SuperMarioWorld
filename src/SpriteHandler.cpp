/*
	SpriteHandler: All operations from retrieving the textures to deciding which sprites to display
*/

#include "GraphicsEngine.hpp"

const int GraphicsEngine::FramesBetweenAnimationChanges = 7;
const std::string GraphicsEngine::texturesPath = "../assets/sprites/";

void GraphicsEngine::LoadTextures()
{
	LoadTexturesFromFile("background");
	LoadTexturesFromFile("floor");
	LoadTexturesFromFile("mario");
	LoadTexturesFromFile("item");
}

void GraphicsEngine::LoadTexturesFromFile(std::string _fileName)
{
	/* Each line looks like "state 00 00 00 00 " with the numbers being left top right bottom */
	std::string buffer;
	std::vector<std::string> splittedBuffer;
	std::string tmpStateName;
	sf::IntRect tmpCoordinates;

	std::string imgFileName = GraphicsEngine::texturesPath + _fileName + ".png";
	std::string rectFileName = GraphicsEngine::texturesPath + _fileName + ".rect";

	std::ifstream rectFile;
	rectFile.open(rectFileName);

	while (getline(rectFile, buffer))
	{
		if (buffer == "")
			continue;

		splittedBuffer = Util::Split(buffer, ' ');

		if (splittedBuffer.size() != 5)
		{
			std::cerr << "Error: wrong number of items for state " << tmpStateName << " in file " << _fileName << ".rect" << std::endl;
			continue;
		}

		try
		{
			tmpStateName = splittedBuffer[0];
			tmpCoordinates.left = std::stoi(splittedBuffer[1]);
			tmpCoordinates.top = std::stoi(splittedBuffer[2]);
			tmpCoordinates.width = std::stoi(splittedBuffer[3]) - tmpCoordinates.left;
			tmpCoordinates.height = std::stoi(splittedBuffer[4]) - tmpCoordinates.top;
			m_textures[_fileName + "_" + tmpStateName].loadFromFile(texturesPath + _fileName + ".png", tmpCoordinates);
		}
		catch (std::invalid_argument err)
		{
			std::cerr << "Error trying to parse state " << tmpStateName << " in file " << _fileName << ".rect: " << err.what() << std::endl;
		}
	}

	rectFile.close();
}

void GraphicsEngine::ResetSpritesToDraw()
{
	while (!m_backgroundToDraw.empty())
		m_backgroundToDraw.pop_back();
	while (!m_levelStructureToDraw.empty())
		m_levelStructureToDraw.pop_back();
	while (!m_displayableObjectsToDraw.empty())
		m_displayableObjectsToDraw.pop_back();
}

void GraphicsEngine::SetBackgroundToDraw()
{
	ResetTmpSprite();
	m_tmpSprite->setTexture(m_textures["background_" + m_currentBackgroundName]);
	m_backgroundToDraw.push_back(*m_tmpSprite);
}

void GraphicsEngine::SetFloorToDraw()
{
	SetListOfDisplayablesToDraw(m_listFloorTileNames, "floor_");
}

void GraphicsEngine::SetForegroundToDraw()
{
	SetListOfDisplayablesToDraw(m_listForegroundItemsTileNames, "item_");
}

void GraphicsEngine::SetListOfDisplayablesToDraw(std::map<DisplayableObject, std::string, CompareDisplayableObjects>& _list, std::string _texturePrefix)
{
	EngineEvent tmpEvent;
	std::string spriteName;

	ResetTmpSprite();
	for (std::map<DisplayableObject, std::string, CompareDisplayableObjects>::iterator it = _list.begin(); it != _list.end(); ++it)
	{
		spriteName = GetTextureNameFromDisplayInfo(it->first.GetID(), _texturePrefix + it->second, NO_STATE);
		m_tmpSprite->setTexture(m_textures[spriteName]);
		m_tmpSprite->setPosition(it->first.GetPosition());
		m_levelStructureToDraw.push_back(*m_tmpSprite);

		// Tell GameEngine what is to be drawn (id and coordinates), so it can handle collisions
		tmpEvent.set(INFO_POS_LVL, it->first.GetID(), m_tmpSprite->getGlobalBounds());
		m_engines["g"]->PushEvent(tmpEvent);
	}
}

void GraphicsEngine::SetDisplayableObjectToDraw(InfoForDisplay _info)
{
	ResetTmpSprite();
	std::string spriteName = GetTextureNameFromDisplayInfo(_info.id, _info.name, _info.state);
	m_tmpSprite->setTexture(m_textures[spriteName]);
	m_tmpSprite->setPosition(sf::Vector2f(_info.coordinates.x, _info.coordinates.y));
	if (_info.reverse)
	{
		float height = m_tmpSprite->getGlobalBounds().height;
		float width = m_tmpSprite->getGlobalBounds().width;
		m_tmpSprite->setTextureRect(sf::IntRect(width, 0, -width, height));
	}
	m_displayableObjectsToDraw.push_back(*m_tmpSprite);

	// Tell GameEngine what is to be drawn (id and coordinates), so it can handle collisions
	EngineEvent tmpEvent;
	tmpEvent.set(INFO_POS_LVL, _info.id, m_tmpSprite->getGlobalBounds());
	m_engines["g"]->PushEvent(tmpEvent);

#ifdef DEBUG_MODE
	if (_info.name == "mario")
		m_posMario = _info.coordinates;
#endif
}

/* Figures out which sprite to display, ie the name of the sprite in the RECT file */
std::string GraphicsEngine::GetTextureNameFromDisplayInfo(int _id, std::string _name, State _state)
{
	std::string test;
	switch (_state)
	{
		case UNKNOWN:
		case STATIC:
			return GetTextureNameFromStateName(_id, _name + "_static");
		case RUN:
		case WALK:
			return GetTextureNameFromStateName(_id, _name + "_walk");
		case JUMP:
			return GetTextureNameFromStateName(_id, _name + "_jump");
		case FALL:
			return GetTextureNameFromStateName(_id, _name + "_fall");
		case NO_STATE:
			return GetTextureNameFromStateName(_id, _name);
		default:
			assert(false);
			return NULL;
	}
}

std::string GraphicsEngine::GetTextureNameFromStateName(int _id, std::string _stateName)
{
	std::string textureName;
	int nbTextures = HowManyLoadedTexturesContainThisName(_stateName);
	assert(nbTextures > 0);

	if (nbTextures == 1)			// Static
		textureName = _stateName;
	else							// Animation
		textureName = FindNextTextureName(_id, _stateName, nbTextures);

	m_spritesCurrentlyDisplayed[_id] = textureName;
	return textureName;
}

int GraphicsEngine::HowManyLoadedTexturesContainThisName(std::string _stateName)
{
	// Counts the number of textures that are either exactly _stateName (static), or smth like _stateName + "2" (animation)
	int nb = 0;
	for (std::map<std::string, sf::Texture>::iterator it = m_textures.begin(); it != m_textures.end(); ++it)
	{
		if (it->first == _stateName)
			return 1; // Found the exact name, ie a static sprite

		if (it->first.compare(0, _stateName.length(), _stateName) == 0 && Util::isInteger(it->first.substr(_stateName.length())))
			nb++; // Found the name followed by a number, ie a frame of an animation
	}
	return nb == 1 ? 0 : nb; // nb == 1 here means that _stateName == "walk" and there is no "walk" in the map, but rather a "walk1", and this is a problem (this would be an animation with only 1 sprite)
}

std::string GraphicsEngine::FindNextTextureName(int _id, std::string _stateName, int _nbTextures)
{
	static int framesSinceLastChange = 0;

	std::string currentTextureName = m_spritesCurrentlyDisplayed[_id];
	if (currentTextureName == "" || currentTextureName.find(_stateName) == std::string::npos) // If it's the first time we are displaying this id OR if we are beginning the animation
		return _stateName + "1";

	assert(HowManyLoadedTexturesContainThisName(_stateName) > 1);

	// We are now ready to display the next sprite of the animation but we can't display a new sprite at every frame, that's too fast. So we use FramesBetweenAnimationChanges.
	framesSinceLastChange++;
	if (framesSinceLastChange % GraphicsEngine::FramesBetweenAnimationChanges != 0)
		return currentTextureName;
	else
		framesSinceLastChange = 0;

	int nbCurrentFrame = std::stoi(currentTextureName.substr(_stateName.length())); // currentTextureName is like mario_walk2 and _stateName is like mario_walk ==> we get the 2
	return _stateName + (nbCurrentFrame == _nbTextures ? "1" : std::to_string(++nbCurrentFrame));
}

void GraphicsEngine::ResetTmpSprite()
{
	delete m_tmpSprite;
	m_tmpSprite = new sf::Sprite();
}