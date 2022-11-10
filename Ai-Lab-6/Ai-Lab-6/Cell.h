
#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "ScreenSize.h"
#include <list>

class Cell
{
	sf::RectangleShape cellShape;
	std::vector<int> neighborVector;
	int id = 0;
	bool isEndPoint = false;
	bool isStartPoint = false;
	bool isObstaclePoint = false;
	int cost;
public:
	std::vector<int> neighbourList;
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
	void addNeighbours(int t_id);
	int getID();
	sf::RectangleShape getCellShape();
	void addCost(int m_cost);
	bool getIsObstaclePoint();
	int getCost();
	void setColor(sf::Vector3f t_RGBValue);
};