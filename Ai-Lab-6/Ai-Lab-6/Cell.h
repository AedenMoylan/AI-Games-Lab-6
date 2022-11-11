
#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "ScreenSize.h"
#include <list>

class Cell
{
	sf::RectangleShape cellShape;
	//std::vector<int> neighborVector;
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
	//void addNeighbours(int t_id);
	int getID();
	sf::RectangleShape getCellShape();
	void addCost(int m_cost);
	bool getIsObstaclePoint();
	int getCost();
	void setColor(sf::Vector3f t_RGBValue);

	bool isMarked;
	Cell* m_previous;
	Cell* previous() const { return m_previous; }

	void setPrevious(Cell* previous) { m_previous = previous; }
	void setMarked(bool t_marked) { isMarked = t_marked; };

	bool marked() const { return isMarked; }
	float m_pathCost;
	float m_h;

	std::vector<int> m_neighbours;
	void addNeighbour(int t_cellID)
	{
		m_neighbours.push_back(t_cellID);
	}

	bool isTraversable;

	std::vector<int> m_diagonalList;
};