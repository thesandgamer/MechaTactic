#pragma once
#include "raylib.h"
#include "Grid.h"

class Actor
{

public:
	Actor();
	Actor(Vector2 positionP);
	Actor(Vector2 positionP, Texture2D spriteP);

	void Init();
	void Draw();
	void Update() {};

	Vector2 position;
	Grid* gridRef;


	bool isActive = true;	

protected:
	Texture2D sprite;


};

