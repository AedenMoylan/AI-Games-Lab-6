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
	int endID;
public:
	void init();
	void selectStartPosition(sf::RenderWindow& t_window);
	void selectEndPosition(sf::RenderWindow& t_window);
	void selectObstaclePosition(sf::RenderWindow& t_window);
	void setupGrid();
	void render(sf::RenderWindow& t_window);
	void setUpText(sf::Font& m_font);
	void setNeighbours();
	void makeCost();
	void verticalCells(int t_point, int t_row, int t_cost);
	void horizontalCells(int t_point, int t_col, int t_cost);
	void setObstacleCost();
	void setCostText();
	void setCost(int t_p, int t_col, int t_cal, int t_cost);
	void update();

};
