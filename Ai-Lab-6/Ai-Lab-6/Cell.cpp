#include "Cell.h"

void Cell::init()
{
    cost = -10;
    vectorShape.setFillColor(sf::Color::Cyan) ;
    vectorShape.setSize(sf::Vector2f(4,16));
    vectorShape.setOrigin(sf::Vector2f(2, 8));
}

void Cell::setStartColour()
{
    cellShape.setFillColor(sf::Color::Blue);
}

void Cell::setEndColour()
{
    cellShape.setFillColor(sf::Color::Yellow);
}

void Cell::setObstacleColour()
{
    cellShape.setFillColor(sf::Color(180.0f,180.0f,180.0f));
}

int Cell::getID()
{
    return id;
}


void Cell::setEndPoint(bool t_isEndPointSelected)
{
    isEndPoint = t_isEndPointSelected;
}

void Cell::setStartPoint(bool t_isStartPointSelected)
{
    isStartPoint = t_isStartPointSelected;
}

void Cell::setObstaclePoint(bool t_isObstaclePointSelected)
{
    isObstaclePoint = t_isObstaclePointSelected;
}

void Cell::setID(int t_id)
{
    id = t_id;
}

void Cell::setPos(sf::Vector2f t_pos)
{
    cellShape.setPosition(t_pos);
}

sf::RectangleShape Cell::getCellShape()
{
    return cellShape;
}

void Cell::initRect()
{
    cellShape.setFillColor(sf::Color::Transparent);
    cellShape.setOutlineColor(sf::Color::Black);
    cellShape.setOutlineThickness(1.5f);
    cellShape.setSize(sf::Vector2f{ ScreenSize::WIDTH / 50,ScreenSize::HEIGHT / 50 });
}

void Cell::addCost(int m_cost)
{
    cost = m_cost;
}

bool Cell::getIsObstaclePoint()
{
    return isObstaclePoint;
}

int Cell::getCost()
{
    return cost;
}

void Cell::setColor(sf::Vector3f t_RGBValue)
{
    sf::Uint8 red = t_RGBValue.x;
    sf::Uint8 green = t_RGBValue.y;
    sf::Uint8 blue = t_RGBValue.z;
    cellShape.setFillColor(sf::Color{ red, green ,blue });
}

Cell* Cell::previous()
{
    return m_previous; 
}

void Cell::setPrevious(Cell* previous)
{
    m_previous = previous;
}

void Cell::setMarked(bool t_marked)
{
    isMarked = t_marked;
}

bool Cell::marked()
{
    return isMarked;
}

void Cell::addNeighbour(int t_cellID)
{
    m_neighbours.push_back(t_cellID);
}
