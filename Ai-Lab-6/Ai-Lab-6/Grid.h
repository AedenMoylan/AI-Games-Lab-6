#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "ScreenSize.h"
#include "Cell.h"
#include <vector>

using namespace std;


class Grid
{
	Cell cell;
	std::vector<Cell> gridVector;
	const static int MAX_CELLS = 2500;
	const static int MAX_ROWS = 50;
	const static int MAX_COLS = 50;
	const static int MAX_OBSTACLES = 500;
	bool isStartPositionSelected;
	bool isEndPositionSelected;
	bool areObstaclesSelected;
	sf::Text costText[MAX_CELLS];
	Cell* atIndex(int t_id);
public:
	void init();
	void selectStartPosition(sf::RenderWindow& t_window);
	void selectEndPosition(sf::RenderWindow& t_window);
	void selectObstaclePosition(sf::RenderWindow& t_window);
	void setupGrid();
	void render(sf::RenderWindow& t_window);
	void setUpText(sf::Font& m_font);
	/*void neighbours(int t_row, int t_col, int t_current);*/
	void setNeighbours();
	void update();

};
