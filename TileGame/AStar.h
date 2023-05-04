#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

#include "Vector2AStar.h"
#include "Node.h"
#include "List.h"
#include "Graph.h"
#include "AStartUtility.h"

class AStar
{
public:
	AStar(const int width, const int height);
	AStar();
	~AStar() {};

	std::vector<Vector2> GetPath(Vector2 startPos, Vector2 endPos);

	Graph aStarGrid;

	int GRID_WIDTH;
	int GRID_HEIGHT;

	Node startNode;
	Node goalNode;

	List openList;
	List closedList;

	Node current;


	const AStar& operator=(const AStar& other)
	{
		this->aStarGrid = other.aStarGrid;
		this->GRID_WIDTH = other.GRID_WIDTH;
		this->GRID_HEIGHT = other.GRID_HEIGHT;
		this->startNode = other.startNode;
		this->goalNode = other.goalNode;
		this->openList = other.openList;
		this->closedList = other.closedList;
		this->current = other.current;

		return *this;
	}

private:
	std::vector<Vector2> CalculatePath();
};

