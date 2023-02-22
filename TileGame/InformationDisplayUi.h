#pragma once
#include "InformationDisplay.h"
#include "raylib.h"

class InformationDisplayUi
{
	friend InformationDisplay;

public:
	InformationDisplayUi();
	~InformationDisplayUi();	

	void SetPosition(Vector2 newPos) { position = newPos; }
	Vector2 GetPosition() { return position; }

	void Draw();

	InformationDisplay* infoLinkedTo;


private:
	Vector2 position;
	

};

