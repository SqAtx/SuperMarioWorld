#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "Engine.hpp"
#include "../Utilities/CollisionHandler.hpp"
#include "../Items/Box.hpp"
#include "../Characters/Goomba.hpp"
#include "../Items/Pipe.hpp"
#include "../irrXML/irrXML.h"

/*
    Game engine: Handles the movements of the player, collisions, etc.
*/
class GameEngine : public Engine
{
    public:
        GameEngine(Game *_g);
        ~GameEngine();

		void Frame();
		void Frame(float _dt);

		/* Getters / setters for Collisionhandler */
		void TransmitInfoToGFX(EngineEvent _event) { return m_engines["gfx"]->PushEvent(_event); };
		DisplayableObject *GetForegroundItem(unsigned int _id) { return m_listForegroundItems[_id]; };
		const sf::Vector2f GetCoordinatesOfForegroundItem(unsigned int _id) { return m_listForegroundItems[_id]->GetPosition(); };
		void UpdateForegroundItem(unsigned int _id, sf::FloatRect& _coords) { m_listForegroundItems[_id]->SetCoordinates(_coords); };

    private:
		bool m_levelStarted;
		CollisionHandler *m_collisionHandler;

		sf::Vector2f m_initPosMario;
		int m_indexMario; // Index of Mario in m_characters. -1 if he's not in it.

		std::vector<MovingObject*> m_characters;
		std::map<unsigned int, DisplayableObject*> m_listForegroundItems; // Part of the level the characters can be in collision with. Pointers stored to allow polymorphism.

		void ProcessEvent(EngineEvent& _event);
		void HandlePressedKey(sf::Keyboard::Key _key);
		bool CanRespawnMario();
		void HandleReleasedKey(sf::Keyboard::Key _key);

		void UpdateCharacterPosition(MovingObject& _character, float _dt);
		void CheckCharacterDeath(MovingObject& _character);
		void KillCharacter(MovingObject& _character);
		void SendCharacterPosition(int _indexCharacter);

		void StartLevel(std::string _lvlName);
		int AddCharacterToArray(MovingObject *_character);

		void HandleCollisions(MovingObject& _obj);

		/* 
		 * XML Level 
		 */
		irr::io::IrrXMLReader *m_lvlFile;

		bool LoadLevel(std::string _lvlName);
		void StoreCharactersInitialPositions();
		void StoreListForegroundTileNames();
		void StoreBox();
		void StorePipe();
		PipeType GetPipeTypeFromXML();
		void StoreFloor();

		std::string GetAttributeValue(const char* _name, bool _optionalAttribute = false);
		float GetAttributeValueAsFloat(const char* _name);
		int GameEngine::GetAttributeValueAsInt(const char* _name);
		void SendInfoPosLvlToGFX(InfoForDisplay _info);
		void GetCoordinatesAndTileName(sf::Vector2f *_coords, std::string *_tileName);

		bool m_deathSoundIsPlaying; // No input is taken into account while this sound is playing [see sound engine]

		static const std::string levelsPath;
};

#endif // GAMEENGINE_H
