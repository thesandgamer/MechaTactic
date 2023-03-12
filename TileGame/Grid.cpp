#include "Grid.h"
#include "Game.h"

Grid::Grid(Vector2 pos,int width, int height, int cellWidth, int cellHeight) :gridPosition(pos), GRID_WITH{ width }, GRID_HEIGHT{ height }, CELL_WIDTH{ cellWidth },CELL_HEIGHT{cellHeight}
{
	
}

Grid::Grid() 
{
	GRID_WITH = 0;
	GRID_HEIGHT = 0;
	CELL_WIDTH = 0;
	CELL_HEIGHT = 0;
	gridPosition = { 0,0 };	

	//aStar = 


}

Grid::~Grid()
{
}

void Grid::Start()
{
	grid.resize(GRID_WITH);
	for (std::vector<Tile>& i : grid)
	{
		i.resize(GRID_HEIGHT);
	}
	std::cout << "Grid finish to resize" << std::endl;


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
	aStar = AStar(GRID_WITH, GRID_HEIGHT);
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

bool Grid::IsInGrid(Vector2 pos)
{
	if (pos.x >= 0
		&& pos.y  >= 0
			&& pos.x < ( GRID_WITH   ) 
			&& pos.y < ( GRID_HEIGHT  ))
	{
		return true;
	}
	else
	{

		return false;
	}
}


//Peut peut être être fait en mettant un pointeur et changeant la valeur
Vector2 Grid::PosInGrid(Vector2 pos)
{
	Vector2 newPos;
	newPos.x = (int) (( ( pos.x  -gridPosition.x)/ CELL_WIDTH));
	newPos.y = (int) (( (pos.y - gridPosition.y) / CELL_HEIGHT));

	//std::cout << "Pos in grid: " << newPos.x << " " << newPos.y << std::endl;

	return newPos;
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
	for each (Actor * act in Game::instance().GetElementsInGame())
	{
		aStar.aStarGrid.AddObstacle(act->position);
		//grid[act->position.x][act->position.y].traversible = false;

	}
}
