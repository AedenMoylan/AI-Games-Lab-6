#include "Cell.h"

void Cell::init()
{
}

void Cell::setStartColour()
{
    cellShape.setFillColor(sf::Color::Blue);
}

void Cell::setEndColour()
{
    cellShape.setFillColor(sf::Color::Yellow);
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

void Cell::setNeighbours(Cell* t_neighbour)
{
    m_neighbour.push_back(t_neighbour);
}