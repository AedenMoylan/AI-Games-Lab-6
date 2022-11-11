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

	for (int i = 0; i < 200; i++)
	{
		m_pathITtake[i].setSize(sf::Vector2f(30.0f, 30.0f));
		m_pathITtake[i].setFillColor(sf::Color::Yellow);
	}

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
			gridVector.at(id).setEndColour();
			gridVector.at(id).setEndPoint(true);
			endID = id;
			isEndPositionSelected = true;

			makeCost();
			setObstacleCost();
			setCostText();
			//generateHeatMap();
			runaStar(startID, endID);
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
			/*std::cout << "Obstacle Point: " + std::to_string(gridVector.at(randNum).getID()) << std::endl;*/
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
		t_window.draw(gridVector.at(i).getCellShape());
		if (gridVector.at(i).getIsObstaclePoint() == false)
		{
			t_window.draw(costText[i]);
		}
	}

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

//void Grid::setNeighbours()
//{
//	for (int i = 0; i < MAX_CELLS; i++)
//	{
//		int row = i / 50;
//		int col = i % 50;
//
//		for (int direction = 0; direction < 9; direction++) {
//			if (direction == 4) continue;
//
//			int neighbourRow = row + ((direction % 3) - 1);
//			int neighbourColumn = col + ((direction / 3) - 1);
//
//			// out of bound check
//			if (neighbourRow >= 0 && neighbourRow < MAX_ROWS && neighbourColumn >= 0 && neighbourColumn < MAX_COLS) {
//				int id = neighbourRow + (neighbourColumn * MAX_ROWS);// num of rows
//
//				//std::cout << i << std::endl;
//				gridVector.at(i).addNeighbours(neighbourRow + (neighbourColumn * 50));
//			}
//		}
//	}
//}

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
		return (t_n1->m_pathCost + t_n1->getCost() )> (t_n2->m_pathCost + t_n2->getCost());
	}
};

Cell& Grid::returnCell(int t_id)
{
	return gridVector.at(t_id);
}

void Grid::neighbours(int t_row, int t_col, std::vector<Cell>& t_cells, int t_current)
{
	// List all neighbors:
	for (int direction = 0; direction < 9; direction++) {
		if (direction == 4) continue; // Skip 4, this is ourself.

		int n_row = t_row + ((direction % 3) - 1); // Neighbor row
		int n_col = t_col + ((direction / 3) - 1); // Neighbor column

		// Check the bounds:
		if (n_row >= 0 && n_row < MAX_ROWS && n_col >= 0 && n_col < MAX_COLS) {

			// A valid neighbor:
			//std::cout << "Neighbor: " << n_row << "," << n_col << " - " << t_current << std::endl;
			t_cells.at(t_current).addNeighbour(n_row + (n_col * 50));
			// add the cell id 
			if (direction == 0 || direction == 2 || direction == 6 || direction == 8)
			{
				int diagId = t_cells.at(n_row + (n_col * 50)).getID();
				t_cells.at(t_current).m_diagonalList.push_back(t_cells.at(n_row + (n_col * 50)).getID());
			}
		}
	}
}

void Grid::runaStar(int t_start, int t_end)
{
	Cell* start = &gridVector.at(t_start);
	Cell* end = &gridVector.at(t_end);

	aStar(start, end);
}

void Grid::aStar(Cell* start, Cell* dest)
{
	Cell* s = start;
	Cell* goal = dest;

	std::vector<Cell*> childNodes;
	std::priority_queue<Cell*, std::vector<Cell*>, Comparer> pq;

	int distance = std::numeric_limits<int>::max();

	for (int i = 0; i < MAX_CELLS; i++)
	{
		gridVector[i].m_pathCost = distance / 10;
		gridVector[i].setPrevious(nullptr);
		gridVector[i].setMarked(false);
	}

	if (goal != nullptr && s != nullptr)
	{
		s->m_pathCost = 0;
		s->setMarked(true);
		pq.push(s);

		while (pq.size() != 0 && pq.top() != goal)
		{
			auto iter = pq.top()->m_neighbours.begin();
			auto endIter = pq.top()->m_neighbours.end();
			int i = 0;
			for (; iter != endIter; iter++)
			{
				Cell* mychild = &returnCellsArray().at(*iter);
				if (mychild != pq.top()->previous() )
				{
					float arcWeight = 10;
					float distToChild = 0;

					distToChild = (arcWeight + pq.top()->m_pathCost);
					if (distToChild < mychild->m_pathCost)
					{
						mychild->m_pathCost = distToChild;
						mychild->setPrevious(pq.top());

						if (mychild == goal)
						{
							std::cout << "I finish" << std::endl;
						}
					}

					if (mychild->marked() == false)
					{
						pq.push(mychild);
						mychild->setMarked(true);
					}
				}
			}
			pq.pop();
		}
	}
	Cell* pathNode = goal;
	while (pathNode->previous() != nullptr)
	{
		pathNode = pathNode->previous();

		sf::Vector3f colourValue = { 200.0f,255.0f,0.0f };
		pathNode->setColor(colourValue);
	}

	childNodes.clear();
}

void Grid::update()
{

}