

#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "ScreenSize.h"
#include "Grid.h"

class Game
{
public:
	Game();
	~Game();
	void run();

	Grid grid;
private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void update();
	void render();


	sf::RenderWindow m_window;

	bool m_exitGame;

};

#endif 

