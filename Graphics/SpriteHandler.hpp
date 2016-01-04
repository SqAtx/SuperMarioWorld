#ifndef SPRITEHANDLER_H
#define SPRITEHANDLER_H

#include "../System/Util.hpp"

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

		void SetDisplayInfoOnSprite(InfoForDisplay _info, sf::Sprite *_sprite);
		void SpriteHandler::SetTextureOnSprite(std::string _textureName, sf::Sprite *_sprite);

		std::string GetFullStateName(std::string _name, State _state);
		std::string GetTextureNameFromStateName(std::string _stateFullName, Sprite::SpriteInfo& _currentInfo, int _nbTextures);
		int HowManyLoadedTexturesContainThisName(std::string _name);

		static const int FramesBetweenAnimationChanges;
		static const std::string texturesPath;

	private:
		std::map<std::string, sf::Texture> m_textures;

		void LoadTexturesFromFile(std::string _fileName);

		std::string FindNextTextureName(std::string _stateName, Sprite::SpriteInfo& _currentInfo, int _nbTextures);
};

#endif
