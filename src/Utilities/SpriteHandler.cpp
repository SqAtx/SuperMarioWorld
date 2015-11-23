/*
	SpriteHandler: All operations from retrieving the textures to deciding which sprites to display
*/
#include <exception>
#include "../DisplayableObject.hpp"
#include "../Engines/GraphicsEngine.hpp"
#include "SpriteHandler.hpp"

const int SpriteHandler::FramesBetweenAnimationChanges = 7;
const std::string SpriteHandler::texturesPath = "../assets/sprites/";

SpriteHandler::SpriteHandler()
{

}

void SpriteHandler::LoadTextures()
{
	LoadTexturesFromFile("background");
	LoadTexturesFromFile("floor");
	LoadTexturesFromFile("mario");
	LoadTexturesFromFile("goomba");
	LoadTexturesFromFile("item");
}

void SpriteHandler::LoadTexturesFromFile(std::string _fileName)
{
	/* Each line looks like "state 00 00 00 00 " with the numbers being left top right bottom */
	std::string buffer;
	std::vector<std::string> splittedBuffer;
	std::string tmpStateName;
	sf::IntRect tmpCoordinates;

	std::string imgFileName = SpriteHandler::texturesPath + _fileName + ".png";
	std::string rectFileName = SpriteHandler::texturesPath + _fileName + ".rect";

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
			m_textures[_fileName + "_" + tmpStateName].loadFromFile(SpriteHandler::texturesPath + _fileName + ".png", tmpCoordinates);
		}
		catch (std::invalid_argument err)
		{
			std::cerr << "Error trying to parse state " << tmpStateName << " in file " << _fileName << ".rect: " << err.what() << std::endl;
		}
	}

	rectFile.close();
}

sf::Texture& SpriteHandler::GetTexture(std::string _name)
{
	return m_textures[_name];
}

void SpriteHandler::SetDisplayInfoOnSprite(InfoForDisplay _info, sf::Sprite *_sprite)
{
	_sprite->setTexture(m_textures[_info.name]);
	_sprite->setPosition(sf::Vector2f(_info.coordinates.left, _info.coordinates.top));

	if (_info.reverse)
	{
		float height = _sprite->getGlobalBounds().height;
		float width = _sprite->getGlobalBounds().width;
		_sprite->setTextureRect(sf::IntRect(width, 0, -width, height));
	}
}

/* Figures out which sprite to display, ie the name of the sprite in the RECT file */
std::string SpriteHandler::GetFullStateName(std::string _name, State _state)
{
	switch (_state)
	{
		case STATIC:
			return _name + "_static";
		case RUN:
		case WALK:
			return _name + "_walk";
		case JUMP:
			return _name + "_jump";
		case FALL:
			return _name + "_fall";
		case EMPTY:
			return _name + "_empty";
		case UNKNOWN:
		case NORMAL:
			return _name;
		default:
			assert(false);
			return NULL;
	}
}

std::string SpriteHandler::GetTextureNameFromStateName(std::string _stateFullName, std::string _currentTextureName, int _nbTextures)
{
	return _nbTextures == 1 ? _stateFullName : FindNextTextureName(_stateFullName, _currentTextureName, _nbTextures);
}

int SpriteHandler::HowManyLoadedTexturesContainThisName(std::string _stateName)
{
	// Counts the number of textures that are either exactly _stateName (static), or smth like _stateName + "2" (animation)
	int nb = 0;
	std::string frameNumber;
	for (std::map<std::string, sf::Texture>::iterator it = m_textures.begin(); it != m_textures.end(); ++it)
	{
		if (it->first.length() < _stateName.length()) // State name longer than texture name: the texture can't be right
			continue;

		if (it->first == _stateName)
			return 1; // Found the exact name, ie a static sprite

		frameNumber = it->first.substr(_stateName.length());
		if (it->first.compare(0, _stateName.length(), _stateName) == 0 && Util::isInteger(frameNumber))
			nb++; // Found the name followed by a number, ie a frame of an animation
	}
	return nb == 1 ? 0 : nb; // nb == 1 here means that _stateName == "walk" and there is no "walk" in the map, but rather a "walk1", and this is a problem (this would be an animation with only 1 sprite)
}

std::string SpriteHandler::FindNextTextureName(std::string _stateName, std::string _currentTextureName, int _nbTextures)
{
	static int framesSinceLastChange = 0;

	if (_currentTextureName == "" || _currentTextureName.find(_stateName) == std::string::npos) // If it's the first time we are displaying this id OR if we are beginning the animation
		return _stateName + "1";

	if (HowManyLoadedTexturesContainThisName(_stateName) <= 1)
	{
		std::cerr << HowManyLoadedTexturesContainThisName(_stateName) << " texture contain " << _stateName << std::endl;
		assert(false);
	}

	// We are now ready to display the next sprite of the animation but we can't display a new sprite at every frame, that's too fast. So we use FramesBetweenAnimationChanges.
	framesSinceLastChange++;
	if (framesSinceLastChange % SpriteHandler::FramesBetweenAnimationChanges != 0)
		return _currentTextureName;
	else
		framesSinceLastChange = 0;

	int nbCurrentFrame = std::stoi(_currentTextureName.substr(_stateName.length())); // currentTextureName is like mario_walk2 and _stateName is like mario_walk ==> we get the 2
	return _stateName + (nbCurrentFrame == _nbTextures ? "1" : std::to_string(++nbCurrentFrame));
}
