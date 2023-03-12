#pragma once
#include "raylib.h"
#include "InformationDisplay.h"
#include "IInformationPasseur.h"

#include "BoxCollision.h"
class Grid;

class Tile: public IInformationPasseur
{
public:
	Tile();
	Tile(Vector3 positionP);
	Tile(Vector3 positionP,Model modelP);
	~Tile() {};


	bool traversible{ true };

	Grid* refToGrid {nullptr};

	void Init();
	void Draw();

	InformationDisplay* GetInformations() { return informations; }

	string GetInformationOf() override;

	/*
	Tile& operator=(const Tile& other)
	{
		this->pos = other.pos;
		this->width = other.width;
		this->height = other.height;
		this->traversible = other.traversible;
		this->refToGrid = other.refToGrid;
		this->informations = other.informations;

		return *this;
	}	
	*/

private:
	Transform transform{ {0,0,0},{0,0,0},{1,1,1} };

	//-------For drawing-------
	Model model{};
	BoxCollision collision{};
	Color drawColor{ WHITE };

	InformationDisplay* informations;


};

