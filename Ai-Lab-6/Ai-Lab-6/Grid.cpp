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
		gridVector.at(i).init();
	}
	int count = 0;

	player.setFillColor(sf::Color::Magenta);
	player.setRadius(15);
	canPlayerMove = false;

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

			startID = id;
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
			gridVector.at(id).setEndPoint(true);
			endID = id;
			isEndPositionSelected = true;
			for (int i = 0; i < 2500; i++)
			{
				sf::Vector2f endPos = findEndPos(endID);
				float dx = gridVector.at(i).getCellShape().getPosition().x - endPos.x;
				float dy = gridVector.at(i).getCellShape().getPosition().y - endPos.y;

				float rotation = (-atan2(dx, dy) * 180 / 3.14159);
				if (rotation > 0 && rotation < 44 || rotation > 0 - 180 && rotation < 44 - 180)
				{
					rotation = 45;
				}

				if (rotation > 0 -45 && rotation < 44 -45 || rotation > 360 - 44 - 180 && rotation < 360 - 180)
				{
					rotation = -45;
				}



				gridVector.at(i).vectorShape.setRotation(rotation);

			}
			makeCost();
			setObstacleCost();
			setCostText();
			generateHeatMap();
			startAStar(startID, endID);

			gridVector.at(id).setEndColour();
			gridVector.at(startID).setStartColour();
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
		gridVector.at(i).vectorShape.setPosition(gridVector.at(i).getCellShape().getPosition().x + 15, gridVector.at(i).getCellShape().getPosition().y +15);
	}

	for (int i = 0; i < 2500; i++) // 50 * 50 = 2500
	{
		int posY = i / 50;
		int posX = i % 50;
		neighbours(posX, posY, gridVector, i);
	}
}

void Grid::render(sf::RenderWindow& t_window)
{
	for (int i = 0; i < MAX_CELLS; i++)
	{
		//t_window.draw(gridVector.at(i).vectorShape);
		t_window.draw(gridVector.at(i).getCellShape());
		if (gridVector.at(i).getIsObstaclePoint() == false)
		{
			t_window.draw(gridVector.at(i).vectorShape);
			t_window.draw(costText[i]);
		}
	}
	t_window.draw(player);

}

void Grid::setUpText(sf::Font& m_font)
{
	for (int i = 0; i < MAX_CELLS; i++)
	{
		costText[i].setFont(m_font);
		costText[i].setCharacterSize(15);
		costText[i].setFillColor(sf::Color::Black);
	}
}

void Grid::makeCost()
{
	int cost = 0;
	if (gridVector.at(endID).getIsObstaclePoint() == false)
	{
		gridVector[endID].addCost(cost);
		verticalCells(endID, MAX_ROWS, cost);
		verticalCells(endID, -MAX_ROWS, cost);
		horizontalCells(endID, +1, cost);
		horizontalCells(endID, -1, cost);

		setCost(endID, -MAX_COLS, -1, cost);
		setCost(endID, -MAX_COLS, +1, cost);
		setCost(endID, +MAX_COLS, -1, cost);
		setCost(endID, +MAX_COLS, +1, cost);
	}
}

void Grid::verticalCells(int t_point, int t_row, int t_cost)
{
	int point = t_point;
	int newCost = t_cost;
	while (point >= 0 && point < MAX_CELLS)
	{
		gridVector[point].addCost(newCost);
		point += t_row;
		newCost++;
	}
}

void Grid::horizontalCells(int t_point, int t_column, int t_cost)
{
	int point = t_point + t_column;
	int newCost = t_cost + 1;

	if (t_column > 0)
	{
		while (point % MAX_COLS <= MAX_COLS - 1 && point % MAX_COLS != 0)
		{
			gridVector[point].addCost(newCost);
			point += t_column;
			newCost++;
		}
	}
	else if (t_column < 0)
	{
		while (point % MAX_COLS != MAX_COLS - 1 && point % MAX_COLS >= 0)
		{
			gridVector[point].addCost(newCost);
			point += t_column;
			newCost++;
		}
	}
}

void Grid::setCost(int t_point, int t_column, int t_costDifferenceNumber, int t_cost)
{
	int pointID = t_point + t_column + t_costDifferenceNumber;

	if (pointID > 0 && pointID < MAX_CELLS && t_point % 50 == 0)
	{
		gridVector[pointID].addCost(t_cost + 1);
		verticalCells(pointID, t_column, t_cost + 1);
		verticalCells(pointID, t_column, t_cost + 1);
	}
	if (pointID > 0 && pointID < MAX_CELLS && t_point % 50 >= 50 - 1)
	{
		gridVector[pointID].addCost(t_cost + 1);
		verticalCells(pointID, t_column, t_cost + 1);
		verticalCells(pointID, t_column, t_cost + 1);
	}
	else if (pointID >= 0 && pointID < MAX_CELLS)
	{
		gridVector[pointID].addCost(t_cost);
		setCost(pointID, t_column, t_costDifferenceNumber, t_cost + 1);
		verticalCells(pointID, t_column, t_cost + 1);
		verticalCells(pointID, t_column, t_cost + 1);
		horizontalCells(pointID, t_costDifferenceNumber, t_cost + 1);
	}
}

void Grid::setObstacleCost()
{
	for (int i = 0; i < 2500; i++)
	{
		if (gridVector.at(i).getIsObstaclePoint() == true) {

			gridVector[i].addCost(99999);
			gridVector[i].isTraversable = false;
		}
	}
}

void Grid::setCostText()
{
	for (int i = 0; i < MAX_CELLS; i++)
	{
		int test = gridVector.at(i).getCost();
		costText[i].setString(std::to_string(test));
	}
}

void Grid::generateHeatMap()
{
	float redColourValue = 255.0f;

	for (int i = 0; i < MAX_CELLS; i++)
	{
		if (gridVector.at(i).getIsObstaclePoint() == false)
		{
			sf::Vector3f colourValue = { redColourValue - (gridVector.at(i).getCost() * 8) ,0.0f,0.0f };
			if (colourValue.x < 50)
			{
				colourValue.x = 50;
			}
			gridVector.at(i).setColor(colourValue);
		}
	}
}

class Comparer
{
public:
	bool operator()(Cell* t_n1, Cell* t_n2) const
	{
		return (t_n1->pathCost + t_n1->getCost() )> (t_n2->pathCost + t_n2->getCost());
	}
};

Cell& Grid::returnCell(int t_id)
{
	return gridVector.at(t_id);
}

sf::Vector2f Grid::findEndPos(int t_myId)
{
	for (int i = 0; i < MAX_CELLS; i++)
	{
		return gridVector.at(t_myId).getCellShape().getPosition();

	}
}

void Grid::neighbours(int t_row, int t_col, std::vector<Cell>& t_cells, int t_current)
{
	// List all neighbors:
	for (int direction = 0; direction < 9; direction++) 
	{
		if (direction == 4) // 4 is us
		{
			continue;
		}

		int row = t_row + ((direction % 3) - 1); // Neighbor row
		int col = t_col + ((direction / 3) - 1); // Neighbor column

		// boundary check
		if (row >= 0 && row < MAX_ROWS && col >= 0 && col < MAX_COLS) 
		{
			t_cells.at(t_current).addNeighbour(row + (col * 50));
		}
	}
}

void Grid::startAStar(int t_start, int t_end)
{
	Cell* start = &gridVector.at(t_start);
	Cell* end = &gridVector.at(t_end);

	aStar(start, end);
}

void Grid::aStar(Cell* t_start, Cell* t_end)
{
	Cell* start = t_start;
	Cell* goal = t_end;

	std::priority_queue<Cell*, std::vector<Cell*>, Comparer> pq;

	int distance = std::numeric_limits<int>::max();

	for (int i = 0; i < MAX_CELLS; i++)
	{
		gridVector[i].pathCost = distance / 10;
		gridVector[i].setPrevious(nullptr);
		gridVector[i].setMarked(false);
	}

	if (goal != nullptr && start != nullptr)
	{
		start->pathCost = 0;
		start->setMarked(true);
		pq.push(start);

		while (pq.size() != 0 && pq.top() != goal)
		{
			auto iter = pq.top()->m_neighbours.begin();
			auto endIter = pq.top()->m_neighbours.end();
			int i = 0;
			for (; iter != endIter; iter++)
			{
				Cell* child = &returnCellsArray().at(*iter);
				if (child != pq.top()->previous() )
				{
					float arcWeight = 10;
					float distanceToChild = 0;

					distanceToChild = (arcWeight + pq.top()->pathCost);
					if (distanceToChild < child->pathCost)
					{
						child->pathCost = distanceToChild;
						child->setPrevious(pq.top());

						if (child == goal)
						{
							std::cout << "end" << std::endl;
						}
					}

					if (child->marked() == false)
					{
						pq.push(child);
						child->setMarked(true);
					}
				}
			}
			pq.pop();
		}
	}
	Cell* pathNode = goal;
	Cell* pathNode2 = goal;
	while (pathNode->previous() != nullptr)
	{
		playerPath.push(pathNode);
		pathNode = pathNode->previous();
		sf::Vector3f colourValue = { 200.0f,255.0f,0.0f };
		pathNode->setColor(colourValue);
	}

	//for (auto i = 49; i >= 0; i--)
	//{
	//	playerPath2[i] = pathNode2->getID();
	//	pathNode2 = pathNode2->previous();
	//}

	canPlayerMove = true;
	player.setPosition(playerPath.top()->getCellShape().getPosition());
}

void Grid::update()
{
	if (canPlayerMove == true)
	{
		if (player.getPosition() != gridVector.at(endID).getCellShape().getPosition())
		{
			movePlayer(playerPath);
		}		
	}
}

void Grid::movePlayer(std::stack<Cell*> t_path)
{
	if (player.getPosition().x > t_path.top()->getCellShape().getPosition().x)
	{
		player.move(-1, 0);
	}
	if (player.getPosition().x < t_path.top()->getCellShape().getPosition().x)
	{
		player.move(1, 0);
	}
	if (player.getPosition().y >  t_path.top()->getCellShape().getPosition().y)
	{
		player.move(0, -1);
	}
	if (player.getPosition().y < t_path.top()->getCellShape().getPosition().y)
	{
		player.move(0, 1);
	}
	if (player.getPosition() == t_path.top()->getCellShape().getPosition())
	{
		playerPath.pop();
	}
}