#ifndef GRAPHICSENGINE_H
#define GRAPHICSENGINE_H

#include "Engine.hpp"
#include "../Utilities/SpriteHandler.hpp"

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
		SpriteHandler *m_spriteHandler;
		static const float FramerateLimit;

		sf::Vector2f m_levelSize;
		sf::Vector2f m_cameraPosition;

		sf::Sprite* m_tmpSprite;
		std::string m_currentBackgroundName;

		// Sprites to draw: 3 levels
		std::vector<sf::Sprite> m_backgroundToDraw;
		std::vector<sf::Sprite> m_levelStructureToDraw;
		std::map<unsigned int, sf::Sprite> m_displayableObjectsToDraw;

		// List of all the foreground tiles in the current level and their coordinates
		std::map<unsigned int, InfoForDisplay> m_listForegroundItems;
		std::map<unsigned int, InfoForDisplay> m_listPipes; // The pipes are special because they need to be displayed last in order to hide whatever they contain
		void UpdateForegroundItem(InfoForDisplay _info);

		std::map<unsigned int, std::string> m_spritesCurrentlyDisplayed; // Contains id of displayable object and which sprite (name from RECT file) is displayed ATM
		std::map<unsigned int, Sprite::StaticOrAnimated> m_animationStates; // One for each DisplayableObject

		void ProcessEvent(EngineEvent& _event);
		void ProcessWindowEvents();

		std::string GetTextureName(unsigned int _id, std::string _name, State _state);
		void UpdateAnimationStates(unsigned int _id, std::string _stateFullName, int nbTextures);

		void ResetSpritesToDraw();

		void DisplayWindow();

		// Add sprites in m_toDraw: the farthest first
		void SetBackgroundToDraw();
		void SetForegroundToDraw();
		void SetListOfDisplayablesToDraw(std::map<unsigned int, InfoForDisplay>& _list);
		void SetLevelStructureObjectToDraw(InfoForDisplay _info);
		void SetDisplayableObjectToDraw(InfoForDisplay _info);

		void DrawGame();

		void StoreLevelInfo(LevelInfo _info);

		void ResetTmpSprite();

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
