#pragma once
#include <iostream>
#include "raylib.h"
#include <vector>

#include "Tile.h"
#include "AStar.h"

class Grid: public Actor
{
public:
	Grid(Vector3 pos,Vector3 gridSize, int cellWidth, int cellLength,int cellHeight);
	Grid();
	~Grid();

	void Start();
	void Init() override;
	void Draw() override;
	void Update() override;


	Vector3 GRID_SIZE;
	
	int CELL_WIDTH;
	int CELL_LENGTH;
	int CELL_HEIGHT;

	std::vector<std::vector<Tile>> grid;

	AStar aStar;

	Vector3 GetGridPos() { return gridPosition; }
	
	bool IsInGrid(Vector3 pos);

	Vector3 PosInGrid(Vector3 pos);

	Vector3 PosInGridToPosToWorld(Vector3 pos);

	void Debug_CleanPathVisibility();

	void CalculateObstacles();

	Texture2D spriteOfTiles;

	/*
	Grid& operator=(const Grid& other)
	{
		this->GRID_WITH = other.GRID_WITH;
		this->GRID_HEIGHT = other.GRID_HEIGHT;
		this->CELL_WIDTH = other.CELL_WIDTH;
		this->CELL_HEIGHT = other.CELL_HEIGHT;
		this->grid = other.grid;
		this->aStar = other.aStar;
		this->gridPosition = other.gridPosition;
		this->spriteOfTiles = other.spriteOfTiles;
		return* this;
	}
	*/
private:
	Vector3 gridPosition;

	
};

