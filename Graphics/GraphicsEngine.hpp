#ifndef GRAPHICSENGINE_H
#define GRAPHICSENGINE_H

#include "../System/Engine.hpp"
#include "../Graphics/SpriteHandler.hpp"

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
        GraphicsEngine(EventEngine*);
        ~GraphicsEngine();

        void Frame();
		float GetFramerateLimit();

		void RceiveLevelInfo(LevelInfo* _info);
		void ReceiveCharacterPosition(InfoForDisplay* _info);

		void RemoveDisplayableObject(unsigned int _id);
		void UpdateForegroundItem(const InfoForDisplay *_info);
		void DeleteForegroundItem(unsigned int _id);

#ifdef DEBUG_MODE
		void StoreDebugInfo(DebugInfo *_info) { m_debugInfo = _info; };
#endif
    private:
		virtual void CreateListeners();

		sf::RenderWindow *m_gameWindow;
		SpriteHandler *m_spriteHandler;
		static const float FramerateLimit;

		sf::Vector2f m_levelSize;
		sf::Vector2f m_cameraPosition;

		sf::Sprite* m_tmpSprite;
		std::string m_currentBackgroundName;

		// Sprites to draw: 3 levels
		std::vector<sf::Sprite> m_backgroundToDraw;
		std::map<unsigned int, sf::Sprite> m_foregroundSpritesToDraw;
		std::map<unsigned int, sf::Sprite> m_pipeSpritesToDraw;
		std::map<unsigned int, sf::Sprite> m_displayableObjectsToDraw;

		std::map<unsigned int, Sprite::SpriteInfo> m_spritesCurrentlyDisplayed; // Contains id of displayable object and info about the sprite currently displayed (name from RECT file)

		std::map<unsigned int, InfoForDisplay*> m_animatedLevelItems;
		
		void ResetSpritesToDraw();
		void UpdateAnimatedLevelSprites();
		void AddOrUpdateAnimatedLevelItem(const InfoForDisplay *_info);
		void ProcessWindowEvents();

		std::string GetTextureName(unsigned int _id, std::string _name, State _state);
		void UpdateAnimationStates(unsigned int _id, std::string _stateFullName, int nbTextures);

		void DisplayWindow();

		// Add sprites in m_toDraw: the farthest first
		void SetBackgroundToDraw();
		void SetDisplayableObjectToDraw(InfoForDisplay _info);

		void DrawGame();

		void StoreLevelInfo(LevelInfo *_info);

		void InitCameraPosition(float _levelHeight);
		void MoveCameraOnMario(sf::FloatRect _coordsMario);
		void MoveEverythingBy(sf::Vector2f _vect);

		void ResetTmpSprite();
	
		sf::Vector2f RelativeToAbsolute(sf::Vector2f _rel);
		sf::FloatRect RelativeToAbsolute(sf::FloatRect _rel);
		sf::Vector2f AbsoluteToRelative(sf::Vector2f _abs);
		sf::FloatRect AbsoluteToRelative(sf::FloatRect _abs);

#ifdef DEBUG_MODE
		sf::Clock m_clock;

		sf::Font m_font;
		sf::Text m_debugText;

		sf::Vector2f m_posMario;
		DebugInfo *m_debugInfo;

		void DrawDebugInfo();
#endif
};

#endif // GRAPHICSENGINE_H
