#include "GraphicsEngine.hpp"

const float GraphicsEngine::FramerateLimit = 60;

GraphicsEngine::GraphicsEngine(Game *_g): Engine (_g)
{
	m_gameWindow = new sf::RenderWindow(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT, 32), "Super Mario !", sf::Style::Titlebar | sf::Style::Close);
	m_tmpSprite = new sf::Sprite();
	LoadTextures();

#ifdef DEBUG_MODE
	m_font.loadFromFile("arial.ttf");
	m_debugText.setFont(m_font);
	m_debugText.setCharacterSize(15);
	m_debugText.setColor(sf::Color::Red);
#endif
}

GraphicsEngine::~GraphicsEngine()
{
	delete m_gameWindow;
}

void GraphicsEngine::Frame()
{
	m_gameWindow->clear();
	ResetSpritesToDraw();
	if (m_gameWindow->isOpen())
		ProcessWindowEvents();
	ProcessQueue();
	DisplayWindow();
}

// Process a single event, sent by another engine
void GraphicsEngine::ProcessEvent(EngineEvent& _event)
{
	switch (_event.m_type)
	{
		case INFO_POS:
			SetDisplayableObjectToDraw(_event.data.m_infoDisplay);
			break;
#ifdef DEBUG_MODE
		case INFO_DEBUG:
			StoreDebugInfo(_event.m_debugInfo);
			break;
#endif
		default:
			break;
	}
}

// Process windows events that have happened since the last loop iteration (sent by SFML)
void GraphicsEngine::ProcessWindowEvents()
{
	sf::Event windowEvent;
	EngineEvent engineEvent;

	while (m_gameWindow->pollEvent(windowEvent))
	{
		switch (windowEvent.type)
		{
			case sf::Event::KeyPressed:
				engineEvent.set(KEY_PRESSED, windowEvent.key.code);
				m_engines["g"]->PushEvent(engineEvent);
				break;
			case sf::Event::KeyReleased:
				engineEvent.set(KEY_RELEASED, windowEvent.key.code);
				m_engines["g"]->PushEvent(engineEvent);
				break;
			case sf::Event::Closed:
				engineEvent.set(GAME_STOPPED);
				m_engines["g"]->PushEvent(engineEvent);
				m_gameWindow->close();
				break;
			default:
				break;
		}
	}
}

void GraphicsEngine::DisplayWindow()
{
	SetBackgroundToDraw();
	SetFloorToDraw();
	DrawGame();

#ifdef DEBUG_MODE
	DrawDebugInfo();
#endif

	m_gameWindow->display();
}

// Draw the 3 layers in the correct order
void GraphicsEngine::DrawGame()
{
	for (unsigned int i = 0; i < m_backgroundToDraw.size(); i++)
		m_gameWindow->draw(m_backgroundToDraw[i]);
	for (unsigned int i = 0; i < m_levelStructureToDraw.size(); i++)
		m_gameWindow->draw(m_levelStructureToDraw[i]);
	for (unsigned int i = 0; i < m_displayableObjectsToDraw.size(); i++)
		m_gameWindow->draw(m_displayableObjectsToDraw[i]);
}

#ifdef DEBUG_MODE
void GraphicsEngine::DrawDebugInfo()
{
	std::string toWrite;
	sf::Vector2f playerPos = m_posMario;
	sf::Vector2f playerVel = m_debugInfo.velocity;
	sf::Vector2f playerAcc = m_debugInfo.acceleration;

	toWrite += (" Framerate = " + std::to_string(floor((int)1 / m_clock.getElapsedTime().asSeconds())) + "\n");
	toWrite += (" Position: { " + std::to_string(playerPos.x) + "; " + std::to_string(playerPos.y) + " }\n");
	toWrite += (" Velocity: { " + std::to_string(playerVel.x) + "; " + std::to_string(playerVel.y) + " }\n");
	toWrite += (" Acceleration: { " + std::to_string(playerAcc.x) + "; " + std::to_string(playerAcc.y) + " }\n");

	m_clock.restart();
	m_debugText.setString(toWrite);
	m_gameWindow->draw(m_debugText);
}
#endif

float GraphicsEngine::GetFramerateLimit()
{
	return GraphicsEngine::FramerateLimit;
}