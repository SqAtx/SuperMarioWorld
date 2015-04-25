/*
	SpriteHandler: All operations from retrieving the textures to deciding whicch sprites to display
*/

#include "GraphicsEngine.hpp"

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
	m_tmpSprite->setTexture(m_textures["background_sky"]);
	m_backgroundToDraw.push_back(*m_tmpSprite);
}

void GraphicsEngine::SetFloorToDraw()
{
	ResetTmpSprite();
	m_tmpSprite->setTexture(m_textures["floor_left"]);
	m_tmpSprite->setPosition(sf::Vector2f(0, WIN_HEIGHT - 16));
	m_levelStructureToDraw.push_back(*m_tmpSprite);

	for (unsigned int i = 1; i < WIDTH_IN_BLOCKS - 1; i++)
	{
		ResetTmpSprite();
		m_tmpSprite->setTexture(m_textures["floor_middle"]);
		m_tmpSprite->setPosition(sf::Vector2f(SIZE_BLOCK * i, WIN_HEIGHT - 16));
		m_levelStructureToDraw.push_back(*m_tmpSprite);
	}

	ResetTmpSprite();
	m_tmpSprite->setTexture(m_textures["floor_right"]);
	m_tmpSprite->setPosition(sf::Vector2f(WIN_WIDTH - 16, WIN_HEIGHT - 16));
	m_levelStructureToDraw.push_back(*m_tmpSprite);
}

void GraphicsEngine::SetDisplayableObjectToDraw(InfoForDisplay _info)
{
	ResetTmpSprite();
	std::string spriteName = GetTextureNameFromDisplayInfo(_info.id, _info.name, _info.state);
	m_tmpSprite->setTexture(m_textures[spriteName]);
	m_tmpSprite->setPosition(sf::Vector2f(_info.coordinates.x, _info.coordinates.y - m_tmpSprite->getGlobalBounds().height));
	if (_info.reverse)
	{
		float height = m_tmpSprite->getGlobalBounds().height;
		float width = m_tmpSprite->getGlobalBounds().width;
		m_tmpSprite->setTextureRect(sf::IntRect(width, 0, -width, height));
	}
	m_displayableObjectsToDraw.push_back(*m_tmpSprite);

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
			test = GetTextureNameFromStateName(_id, _name + "_static");
			break;
		case WALK:
			test = GetTextureNameFromStateName(_id, _name + "_walk");
			break;
		default:
			assert(false);
			return NULL;
	}
	return test;
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
	/*
	*	CAREFUL here !! If I have walk1, walk2 and walk_foo and I call this with walk, it's gonna return 3 instead of 2 !
	*/

	int nb = 0;
	for (std::map<std::string, sf::Texture>::iterator it = m_textures.begin(); it != m_textures.end(); ++it)
	{
		if (it->first.find(_stateName) != std::string::npos)
			nb++;
	}
	return nb;
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