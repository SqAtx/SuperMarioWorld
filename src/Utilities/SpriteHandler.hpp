#ifndef SPRITEHANDLER_H
#define SPRITEHANDLER_H

#include "Util.hpp"

class GraphicsEngine;

/*
SpriteHandler: All operations from retrieving the textures to deciding which sprites to display
*/
class SpriteHandler
{
	public:
		SpriteHandler();

		void LoadTextures(); // Load all textures at beginning of level
		sf::Texture& GetTexture(std::string _name);

		std::string GetFullStateName(std::string _name, State _state);
		std::string GetTextureNameFromStateName(std::string _stateFullName, std::string _currentTextureName, int _nbTextures);
		int HowManyLoadedTexturesContainThisName(std::string _name);

		static const int FramesBetweenAnimationChanges;
		static const std::string texturesPath;

	private:
		std::map<std::string, sf::Texture> m_textures;

		void LoadTexturesFromFile(std::string _fileName);

		std::string FindNextTextureName(std::string _stateName, std::string _currentTextureName, int _nbTextures);
};

#endif
