
#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "ScreenSize.h"
#include <list>

class Cell
{
	sf::RectangleShape cellShape;
	int id = 0;
	bool isEndPoint = false;
	bool isStartPoint = false;
	bool isObstaclePoint = false;
	int cost;
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
	void setMarked(bool t_marked);
	void setPrevious(Cell* previous);
	void addNeighbour(int t_cellID);
	void addCost(int m_cost);
	void setColor(sf::Vector3f t_RGBValue);
	int getID();
	int getCost();
	bool getIsObstaclePoint();
	bool isMarked;
	bool marked();
	bool isTraversable;
	Cell* previous();
	Cell* m_previous;
	float pathCost;
	float m_h;
	std::vector<int> m_neighbours;
	std::vector<int> m_diagonalList;
	sf::RectangleShape getCellShape();

};