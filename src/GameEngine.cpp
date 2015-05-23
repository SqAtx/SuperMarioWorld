#include "GameEngine.hpp"
#include "Game.hpp"


GameEngine::GameEngine(Game *_g): Engine (_g)
{
	mario = new Player("mario", SIZE_BLOCK * 5, 150);
}

GameEngine::~GameEngine()
{
	delete mario;
}

void GameEngine::Frame()
{
	assert(false); // The overloaded Frame function should be called instead
}

void GameEngine::Frame(float _dt)
{
	ProcessQueue();

	// Send Mario's position to gfx
	EngineEvent posMario, debugMario;
	mario->UpdatePosition(_dt);
	posMario.set(INFO_POS, mario->GetInfoForDisplay());
	m_engines["gfx"]->PushEvent(posMario);
#ifdef DEBUG_MODE
	debugMario.set(INFO_DEBUG, mario->GetDebugInfo());
	m_engines["gfx"]->PushEvent(debugMario);
#endif
}

void GameEngine::ProcessEvent(EngineEvent& _event)
{
	switch (_event.m_type)
	{
		case KEY_PRESSED:
			HandlePressedKey(_event.data.m_key);
			break;
		case KEY_RELEASED:
			HandleReleasedKey(_event.data.m_key);
			break;
		case GAME_STOPPED:
			m_parent->Stop();
			break;
		default:
			break;
	}
}

void GameEngine::HandlePressedKey(sf::Keyboard::Key _key)
{
	EngineEvent tmpEvent;
	switch (_key)
	{
		case sf::Keyboard::Left:
			mario->Move(-1);
			break;
		case sf::Keyboard::Right:
			mario->Move(1);
			break;
		case sf::Keyboard::C:
			mario->ToggleRun(true);
			break;
		case sf::Keyboard::Space:
			if (mario->Jump())
			{
				tmpEvent.set(PLAY_SOUND, JUMP_SND);
				m_engines["s"]->PushEvent(tmpEvent);
			}
		default:
			break;
	}
}

void GameEngine::HandleReleasedKey(sf::Keyboard::Key _key)
{
	switch (_key)
	{
		case sf::Keyboard::Left:
		case sf::Keyboard::Right:
			mario->Move(0);
			break;
		case sf::Keyboard::C:
			mario->ToggleRun(false);
			break;
		case sf::Keyboard::Space:
			mario->EndJump();
			break;
		default:
			break;
	}
}