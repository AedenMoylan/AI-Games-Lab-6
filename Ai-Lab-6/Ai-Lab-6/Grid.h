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
	const int MAX_CELLS = 2500;
	const static int MAX_ROWS = 50;
	const static int MAX_COLS = 50;
	bool isStartPositionSelected;
	bool isEndPositionSelected;
public:
	void init();
	void selectStartPosition(sf::RenderWindow& t_window);
	void selectEndPosition(sf::RenderWindow& t_window);
	void setupGrid();
	void render(sf::RenderWindow& t_window);
	void update();

};
