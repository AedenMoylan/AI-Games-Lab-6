
#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "ScreenSize.h"

class Cell
{
	sf::RectangleShape cellShape;
	int id = 0;
	bool isEndPoint = false;
	bool isStartPoint = false;
	bool isObstaclePoint = false;
public:
	void init();
	void setEndPoint(bool t_isEndPointSelected);
	void setStartPoint(bool t_isStartPointSelected);
	void setObstaclePoint(bool t_isObstaclePointSelected);
	void setStartColour();
	void setEndColour();
	void setObstacleColour();
	void setID(int t_id);
	void setPos(sf::Vector2f t_pos);
	void initRect();
	void setNeighbours(Cell* t_neighbour);
	int getID();
	std::vector<Cell*> m_neighbour;
	sf::RectangleShape getCellShape();
};