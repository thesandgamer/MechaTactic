#include "Grid.h"
#include "Game.h"


Grid::Grid(Vector3 pos, Vector3 gridSize): Actor()
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

Vector3 Grid::PosInWorldToPosInGrid(Vector3 pos)
{
	return {
		(pos.x - GetGridPos().x )/ CELL_WIDTH  ,
		(pos.y - GetGridPos().y )/ CELL_HEIGHT ,
		(pos.z - GetGridPos().z ) / CELL_LENGTH ,

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
	//Check tout ce qui peut faire obstacle au déplacement
	//Si une tuile se trouve au même endroit

	for (int i = 0; i < grid.size(); i++)
	{
		for (int j = 0; j < grid[i].size(); j++)
		{
			aStar.aStarGrid.RemoveObstacle({ grid[i][j].posInGrid.x,grid[i][j].posInGrid.z });
			grid[i][j].traversible = true;
		}
	}

	
	for each (Actor * act in Game::instance().GetElementsInGame())//Pour chaque element du jeu
	{
		//problème icic c'est que la position est une position in world
		Vector3 posInGrid = PosInWorldToPosInGrid(act->GetPosition());

		aStar.aStarGrid.AddObstacle({ posInGrid.x,posInGrid.z });
		grid[posInGrid.x][posInGrid.z].traversible = false;
		
		/*
		if (posInGrid.x == grid[posInGrid.x][posInGrid.z].posInGrid.x && posInGrid.z == grid[posInGrid.x][posInGrid.z].posInGrid.z)
		{
			aStar.aStarGrid.AddObstacle({ posInGrid.x,posInGrid.z });
			grid[posInGrid.x][posInGrid.z].traversible = false;
		}
		else
		{
			aStar.aStarGrid.RemoveObstacle({ posInGrid.x,posInGrid.z });
			grid[posInGrid.x][posInGrid.z].traversible = true;
		}
		*/
		

	}
	
}
