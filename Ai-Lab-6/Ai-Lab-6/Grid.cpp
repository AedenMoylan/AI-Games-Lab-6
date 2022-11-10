#include "Grid.h"

void Grid::init()
{
	setupGrid();
	isStartPositionSelected = false;
	isEndPositionSelected = false;
	areObstaclesSelected = false;

	for (int i = 0; i < MAX_CELLS; i++)
	{
		costText[i].setPosition(gridVector.at(i).getCellShape().getPosition());
	}

	int count = 0;

	setNeighbours();

}

void Grid::selectStartPosition(sf::RenderWindow& t_window)
{
	if (isStartPositionSelected == false)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			sf::Vector2f mousePos = sf::Vector2f{ sf::Mouse::getPosition(t_window) };
			int xPos = mousePos.x / 30;
			int yPos = mousePos.y / 30;
			float id = yPos * MAX_ROWS;
			id += xPos;

			std::cout << "Start Point: " + std::to_string(gridVector.at(id).getID()) << std::endl;
			gridVector.at(id).setStartColour();
			gridVector.at(id).setStartPoint(true);
			isStartPositionSelected = true;
		}
	}
}

void Grid::selectEndPosition(sf::RenderWindow& t_window)
{
	if (isEndPositionSelected == false)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			sf::Vector2f mousePos = sf::Vector2f{ sf::Mouse::getPosition(t_window) };
			int xPos = mousePos.x / 30;
			int yPos = mousePos.y / 30;
			float id = yPos * MAX_ROWS;
			id += xPos;

			std::cout << "End Point: " + std::to_string(gridVector.at(id).getID()) << std::endl;
			gridVector.at(id).setEndColour();
			gridVector.at(id).setEndPoint(true);
			isEndPositionSelected = true;
		}
	}
}

void Grid::selectObstaclePosition(sf::RenderWindow& t_window)
{
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	//{
	//	sf::Vector2f mousePos = sf::Vector2f{ sf::Mouse::getPosition(t_window) };
	//	int xPos = mousePos.x / 30;
	//	int yPos = mousePos.y / 30;
	//	float id = yPos * MAX_ROWS;
	//	id += xPos;


	//	std::cout << "Obstacle Point: " + std::to_string(gridVector.at(id).getID()) << std::endl;
	//	gridVector.at(id).setObstacleColour();
	//	gridVector.at(id).setObstaclePoint(true);
	//}
	if (areObstaclesSelected == false)
	{
		for (int i = 0; i < MAX_OBSTACLES; i++)
		{
			int randNum = (rand() % MAX_CELLS) + 1;
			std::cout << "Obstacle Point: " + std::to_string(gridVector.at(randNum).getID()) << std::endl;
			gridVector.at(randNum).setObstacleColour();
			gridVector.at(randNum).setObstaclePoint(true);
		}
		areObstaclesSelected = true;
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
		t_window.draw(costText[i]);
	}

}

void Grid::setUpText(sf::Font& m_font)
{
	for (int i = 0; i < MAX_CELLS; i++)
	{
		costText[i].setFont(m_font);
		costText[i].setCharacterSize(15);
		costText[i].setFillColor(sf::Color::Black);
		costText[i].setString("1");
	}
}

void Grid::setNeighbours()
{
	for (int i = 0; i < MAX_CELLS; i++)
	{
		int row = i / 50;
		int col = i % 50;

		for (int direction = 0; direction < 9; direction++) {
			if (direction == 4) continue;

			int neighbourRow = row + ((direction % 3) - 1);
			int neighbourColumn = col + ((direction / 3) - 1);

			// out of bound check
			if (neighbourRow >= 0 && neighbourRow < MAX_ROWS && neighbourColumn >= 0 && neighbourColumn < MAX_COLS) {
				int id = neighbourRow + (neighbourColumn * MAX_ROWS);// num of rows

				std::cout << i << std::endl;
				gridVector.at(i).addNeighbours(neighbourRow + (neighbourColumn * 50));

			}
		}
	}
}

void Grid::update()
{

}