#include "Grid.h"
#include "Game.h"


Grid::Grid(Vector3 pos, Vector3 gridSize, int cellWidth, int cellLength, int cellHeight): CELL_HEIGHT(cellHeight),CELL_LENGTH(cellLength),CELL_WIDTH(cellWidth), Actor()
{
	gridPosition = pos;
	GRID_SIZE = gridSize;

}

Grid::Grid(): Actor()
{
}

Grid::~Grid()
{
}

void Grid::Start()
{
	
	grid.resize(GRID_SIZE.x);
	for (std::vector<Tile>& i : grid)
	{
		i.resize(GRID_SIZE.z);
	}
	std::cout << "[GRID]----Grid finish to resize" << std::endl;

	//---------Fill grid---------
	
	for (int i = 0; i < grid.size(); i++)
	{
		for (int j = 0; j < grid[i].size(); j++)
		{
			grid[i][j] = Tile( Vector3{(float)i,-1,(float)j} );
			//Set le model
			grid[i][j].refToGrid = this;
			grid[i][j].Init();

		}
	}
		
	//Set la graph de A*
	aStar = AStar(GRID_SIZE.x, GRID_SIZE.z);
}

void Grid::Init()
{
}

void Grid::Update()
{
}

void Grid::Draw()
{
	for (std::vector<Tile> ligne : grid)
	{
		for (Tile tile : ligne)
		{
			tile.Draw();
			//DrawRectangleLines(gridPosition.x + tile.pos.x* CELL_WIDTH, gridPosition.y + tile.pos.y*CELL_HEIGHT, CELL_WIDTH, CELL_HEIGHT, WHITE);

		}
	}

}

bool Grid::IsInGrid(Vector3 pos)
{
	if (pos.x >= 0
		&& pos.y  >= 0
			&& pos.x < ( GRID_SIZE.x) 
			&& pos.y < (GRID_SIZE.z))
	{
		return true;
	}
	else
	{

		return false;
	}
}


//Peut peut être être fait en mettant un pointeur et changeant la valeur
Vector3 Grid::PosInGrid(Vector3 pos)
{
	Vector3 newPos;
	newPos.x = (( (pos.x - gridPosition.x) / CELL_WIDTH));
	newPos.y = (( (pos.y - gridPosition.y) / CELL_HEIGHT));
	newPos.z = (( (pos.z - gridPosition.z) / CELL_LENGTH));

	//std::cout << "Pos in grid: " << newPos.x << " " << newPos.y << std::endl;

	return newPos;
}

Vector3 Grid::PosInGridToPosToWorld(Vector3 pos)
{
	return {
		(pos.x * CELL_WIDTH)  + GetGridPos().x,
		(pos.y * CELL_HEIGHT) + GetGridPos().y,
		(pos.z * CELL_LENGTH) + GetGridPos().z,

	};
}

void Grid::Debug_CleanPathVisibility()
{
	for (int i = 0; i < grid.size() ;i++)
	{
		for (int j = 0; j < grid[i].size(); j++)
		{
		}
	}
}

void Grid::CalculateObstacles()
{
	/*
	for each (Actor * act in Game::instance().GetElementsInGame())
	{
		aStar.aStarGrid.AddObstacle({act->transform.translation.x,act->transform.translation.z);
		//grid[act->position.x][act->position.y].traversible = false;

	}*/
}
