#include "Grid.h"

void Grid::init()
{
	setupGrid();
	isStartPositionSelected = false;
	isEndPositionSelected = false;
}

void Grid::selectStartPosition(sf::RenderWindow& t_window)
{
	sf::Vector2f mousePos = sf::Vector2f{ sf::Mouse::getPosition(t_window) };

	for (int i = 0; i < MAX_CELLS; i++)
	{
		if (gridVector.at(i).getCellShape().getGlobalBounds().contains(mousePos))
		{
			if (isStartPositionSelected == false)
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					std::cout << "Start Point: " + std::to_string(gridVector.at(i).getID()) << std::endl;
					gridVector.at(i).setStartColour();
					gridVector.at(i).setStartPoint(true);
					isStartPositionSelected = true;
				}
			}
		}
	}
}

void Grid::selectEndPosition(sf::RenderWindow& t_window)
{
	sf::Vector2f mousePos = sf::Vector2f{ sf::Mouse::getPosition(t_window) };

	for (int i = 0; i < MAX_CELLS; i++)
	{
		if (gridVector.at(i).getCellShape().getGlobalBounds().contains(mousePos))
		{
			if (isEndPositionSelected == false)
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
				{
					std::cout << "End Point: " + std::to_string(gridVector.at(i).getID()) << std::endl;
					gridVector.at(i).setEndColour();
					gridVector.at(i).setEndPoint(true);
					isEndPositionSelected = true;
				}
			}
		}
	}
}

void Grid::setupGrid()
{
	sf::Vector2f pos{ 0.0f,0.0f };
	for (int i = 0; i < MAX_CELLS; i++)
	{
		cell.initRect();
		cell.setPos(pos);
		pos.x += cell.getCellShape().getSize().x;
		if (pos.x >= ScreenSize::WIDTH)
		{
			pos.y += cell.getCellShape().getSize().y;
			pos.x = 0;
		}
		gridVector.push_back(cell);
		gridVector.at(i).setID(i);
	}
}

void Grid::render(sf::RenderWindow& t_window)
{
	for (int i = 0; i < MAX_CELLS; i++)
	{
		t_window.draw(gridVector.at(i).getCellShape());
	}

}

void Grid::update()
{

}