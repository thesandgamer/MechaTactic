#pragma once
#include "raylib.h"
#include "InformationDisplay.h"
#include "IInformationPasseur.h"

class Grid;

class Tile: public IInformationPasseur
{
public:
	Tile();
	Tile(int xP, int yP);
	Tile(int xP, int yP,float widthP,float heightP);
	~Tile() {};

	Vector2 pos;

	float width;
	float height;

	bool traversible;

	Grid* refToGrid;

	void Init();
	void Draw();

	InformationDisplay* GetInformations() { return informations; }

	string GetInformationOf() override;


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

	Texture2D sprite;
private:
	InformationDisplay* informations;


};

