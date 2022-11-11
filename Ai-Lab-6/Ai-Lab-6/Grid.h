#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "ScreenSize.h"
#include "Cell.h"
#include <vector>
#include <queue>
#include <stack>

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
	int startID;
	sf::CircleShape player;
public:
	void init();
	void selectStartPosition(sf::RenderWindow& t_window);
	void selectEndPosition(sf::RenderWindow& t_window);
	void selectObstaclePosition(sf::RenderWindow& t_window);
	void setupGrid();
	void render(sf::RenderWindow& t_window);
	void setUpText(sf::Font& m_font);
	void makeCost();
	void verticalCells(int t_point, int t_row, int t_cost);
	void horizontalCells(int t_point, int t_col, int t_cost);
	void setObstacleCost();
	void setCostText();
	void setCost(int t_p, int t_col, int t_cal, int t_cost);
	void generateHeatMap();
	void update();
	void neighbours(int t_row, int t_col, std::vector<Cell>& t_cells, int t_current);
	void aStar(Cell* t_start, Cell* t_end);
	std::vector<Cell>& returnCellsArray()
	{
		return gridVector;
	}
	Cell& returnCell(int t_id);
	sf::Vector2f findEndPos(int t_myId);
	void startAStar(int t_start, int t_end);
	void movePlayer(std::stack<Cell*> t_path);
	bool canPlayerMove;
	std::stack<Cell*> playerPath;

};
