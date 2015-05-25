#ifndef GRAPHICSENGINE_H
#define GRAPHICSENGINE_H

#include "Engine.hpp"

#include "irrXML/irrXML.h"
#include <SFML/Graphics.hpp>
#include <fstream>

#define WIN_HEIGHT			432
#define WIN_WIDTH			512
#define SIZE_BLOCK			16
#define HEIGHT_IN_BLOCKS	WIN_HEIGHT / SIZE_BLOCK
#define WIDTH_IN_BLOCKS		WIN_WIDTH / SIZE_BLOCK

/*
    Graphics engine: Handles the graphics of the game: loading sprites and displaying them using SFML
*/
class GraphicsEngine : public Engine
{
    public:
        GraphicsEngine(Game *_g);
        ~GraphicsEngine();

        void Frame();
		float GetFramerateLimit();
		
    private:
		sf::RenderWindow *m_gameWindow;
		static const float FramerateLimit;
		static const int GraphicsEngine::FramesBetweenAnimationChanges;

		std::map<std::string, sf::Texture> m_textures;

		sf::Sprite* m_tmpSprite;
		std::string m_currentBackgroundName;

		// Sprites to draw: 3 levels
		std::vector<sf::Sprite> m_backgroundToDraw;
		std::vector<sf::Sprite> m_levelStructureToDraw;
		std::vector<sf::Sprite> m_displayableObjectsToDraw;

		std::map<int, std::string> m_spritesCurrentlyDisplayed; // Contains id of displayable object and which sprite (name from RECT file) is displayed ATM
		
		void ProcessEvent(EngineEvent& _event);
		void ProcessWindowEvents();

		bool LoadLevel(std::string _lvlName);
		std::string GetAttributeValue(irr::io::IrrXMLReader *_lvlFile, const char* _name);

		void LoadTextures(); // Load all textures at beginning of level
		void LoadTexturesFromFile(std::string _fileName);

		void ResetSpritesToDraw();

		void DisplayWindow();

		// Add sprites in m_toDraw: the farthest first
		void SetBackgroundToDraw();
		void SetFloorToDraw();
		void SetDisplayableObjectToDraw(InfoForDisplay _info);

		std::string GetTextureNameFromDisplayInfo(int _id, std::string _name, State _state);
		std::string GetTextureNameFromStateName(int _id, std::string _name);
		int HowManyLoadedTexturesContainThisName(std::string _name);
		std::string FindNextTextureName(int _id, std::string _name, int _nbTextures);

		void DrawGame();

		void ResetTmpSprite();

		static const std::string texturesPath;
		static const std::string levelsPath;

#ifdef DEBUG_MODE
		sf::Clock m_clock;

		sf::Font m_font;
		sf::Text m_debugText;

		sf::Vector2f m_posMario;
		DebugInfo m_debugInfo;

		void StoreDebugInfo(DebugInfo _info) { m_debugInfo = _info; };
		void DrawDebugInfo();
#endif
};

#endif // GRAPHICSENGINE_H
