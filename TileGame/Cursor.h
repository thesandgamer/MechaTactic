#pragma once
#include <raylib.h>
#include "Grid.h"


enum class CusorState
{
	NOONE,
	SELECT,
	PAWN_HOVERED,
	PAWN_MOVEMENT,
	PAWN_CAN_NOT_MOVE,
	PAWN_POS_BLOCKED,
};

class Cursor
{
public:
	Cursor();
	Cursor(Vector2 positionP);
	~Cursor();

	void Start();
	void Updtate();
	void Draw();

private:
	Vector2 position;

	Vector2 mousePos;
	Vector2 mousePosInGrid;

	Grid* gridRef;

	CusorState state;

};

