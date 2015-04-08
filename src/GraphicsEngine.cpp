#include "GraphicsEngine.hpp"

#ifdef DEBUG_MODE
#include <math.h>
#endif

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

void GraphicsEngine::LoadTextures()
{
	m_textures["background"].loadFromFile("../SuperMario/Sprites/backgrounds.png", sf::IntRect(516, 438, 512, 432));
	m_textures["floor_left"].loadFromFile("../SuperMario/Sprites/ground_tiles.png", sf::IntRect(120, 150, 16, 16));
	m_textures["floor_middle"].loadFromFile("../SuperMario/Sprites/ground_tiles.png", sf::IntRect(137, 150, 16, 16));
	m_textures["floor_right"].loadFromFile("../SuperMario/Sprites/ground_tiles.png", sf::IntRect(154, 150, 16, 16));
	m_textures["mario"].loadFromFile("../SuperMario/Sprites/mario.png", sf::IntRect(5, 60, 13, 28));
}

void GraphicsEngine::Frame()
{
	m_gameWindow->clear();
	ResetSpritesToDraw();
	if (m_gameWindow->isOpen())
		ProcessWindowEvents();
	ProcessQueue();
	DisplayWindow();

	//m_lastFramerate.setString(std::to_string(1 / m_clock.getElapsedTime().asSeconds()));
	//m_clock.restart();
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

void GraphicsEngine::ResetSpritesToDraw()
{
	while (!m_backgroundToDraw.empty())
		m_backgroundToDraw.pop_back();
	while (!m_levelStructureToDraw.empty())
		m_levelStructureToDraw.pop_back();
	while (!m_displayableObjectsToDraw.empty())
		m_displayableObjectsToDraw.pop_back();
}

void GraphicsEngine::SetBackgroundToDraw()
{
	ResetTmpSprite();
	m_tmpSprite->setTexture(m_textures["background"]);
	m_backgroundToDraw.push_back(*m_tmpSprite);
}

void GraphicsEngine::SetFloorToDraw()
{
	ResetTmpSprite();
	m_tmpSprite->setTexture(m_textures["floor_left"]);
	m_tmpSprite->setPosition(sf::Vector2f(0, WIN_HEIGHT - 16));
	m_levelStructureToDraw.push_back(*m_tmpSprite);

	for (unsigned int i = 1; i < WIDTH_IN_BLOCKS - 1; i++)
	{
		ResetTmpSprite();
		m_tmpSprite->setTexture(m_textures["floor_middle"]);
		m_tmpSprite->setPosition(sf::Vector2f(SIZE_BLOCK * i, WIN_HEIGHT - 16));
		m_levelStructureToDraw.push_back(*m_tmpSprite);
	}

	ResetTmpSprite();
	m_tmpSprite->setTexture(m_textures["floor_right"]);
	m_tmpSprite->setPosition(sf::Vector2f(WIN_WIDTH - 16, WIN_HEIGHT - 16));
	m_levelStructureToDraw.push_back(*m_tmpSprite);
}

void GraphicsEngine::SetDisplayableObjectToDraw(InfoForDisplay _info)
{
	ResetTmpSprite();
	m_tmpSprite->setTexture(m_textures[_info.name]);
	m_tmpSprite->setPosition(sf::Vector2f(_info.coordinates.x, _info.coordinates.y - m_tmpSprite->getGlobalBounds().height));
	if (_info.reverse)
	{
		float height = m_tmpSprite->getGlobalBounds().height;
		float width = m_tmpSprite->getGlobalBounds().width;
		m_tmpSprite->setTextureRect(sf::IntRect(width, 0, -width, height));
	}
	m_displayableObjectsToDraw.push_back(*m_tmpSprite);

#ifdef DEBUG_MODE
	if (_info.name == "mario")
		m_posMario = _info.coordinates;
#endif
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

void GraphicsEngine::ResetTmpSprite()
{
	delete m_tmpSprite;
	m_tmpSprite = new sf::Sprite();
}

float GraphicsEngine::GetFramerateLimit()
{
	return GraphicsEngine::FramerateLimit;
}