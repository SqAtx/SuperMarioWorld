#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "Engine.hpp"
#include "Player.hpp"
#include "Box.hpp"
#include "Goomba.hpp"
#include "Pipe.hpp"
#include "irrXML/irrXML.h"

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

    private:
		bool m_levelStarted;

		sf::Vector2f m_initPosMario;
		int m_indexMario; // Index of Mario in m_characters. -1 if he's not in it.

		std::vector<MovingObject*> m_characters;
		std::map<unsigned int, DisplayableObject*> m_listForegroundItems; // Part of the level the characters can be in collision with. Pointers stored to allow polymorphism.

		void ProcessEvent(EngineEvent& _event);
		void HandlePressedKey(sf::Keyboard::Key _key);
		void HandleReleasedKey(sf::Keyboard::Key _key);

		void CheckCharacterDeath(MovingObject& _character);
		void KillCharacter(MovingObject& _character);
		void SendCharacterPosition(int _indexCharacter);

		void UpdateCharacterPosition(MovingObject& _character, float _dt);
		void HandleCollisionsWithMapEdges(MovingObject& _obj);
		void HandleCollisionsWithLevel(MovingObject& _obj);
		CollisionDirection HandleCollisionWithRect(unsigned int _objId, sf::FloatRect _ref);
		CollisionDirection DetectCollisionWithRect(unsigned int _objId, sf::FloatRect _ref);
		void ReactToCollision(unsigned int _objId, sf::FloatRect _ref, CollisionDirection _direction);

		void StartLevel(std::string _lvlName);
		int AddCharacterToArray(MovingObject *_character);

		bool LoadLevel(std::string _lvlName);
		void StoreCharactersInitialPositions(irr::io::IrrXMLReader *_lvlFile);
		void StoreListForegroundTileNames(irr::io::IrrXMLReader *_lvlFile);
		void StoreBox(irr::io::IrrXMLReader *_lvlFile);
		void StorePipe(irr::io::IrrXMLReader *_lvlFile);
		void StoreFloor(irr::io::IrrXMLReader *_lvlFile);

		std::string GetAttributeValue(irr::io::IrrXMLReader *_lvlFile, const char* _name, bool _optionalAttribute = false);
		float GetAttributeValueAsFloat(irr::io::IrrXMLReader *_lvlFile, const char* _name);
		void SendInfoPosLvlToGFX(InfoForDisplay _info);
		void GameEngine::GetCoordinatesAndTileName(irr::io::IrrXMLReader *_lvlFile, sf::Vector2f *_coords, std::string *_tileName);

		static const std::string levelsPath;
};

#endif // GAMEENGINE_H
