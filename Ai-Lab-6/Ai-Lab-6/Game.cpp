#include "Game.h"

Game::Game() :
	m_window{ sf::VideoMode{ ScreenSize::WIDTH, ScreenSize::HEIGHT, 32U }, "AI Lab 6" }, m_exitGame{ false }
{
	grid.init();
}

Game::~Game()
{

}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float FPS{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / FPS);
	while (m_window.isOpen())
	{
		processEvents();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents();
			update();
		}
		render();

		if (m_exitGame == true)
		{
			m_window.close();
		}
	}
}

void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if (sf::Event::KeyPressed == newEvent.type)
		{
			processKeys(newEvent);
		}
	}
}



void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
}


void Game::update()
{
	grid.update();
	grid.selectStartPosition(m_window);
	grid.selectEndPosition(m_window);
	grid.selectObstaclePosition(m_window);
}


void Game::render()
{
	m_window.clear(sf::Color{100,100,100});
	grid.render(m_window);


	m_window.display();
}


