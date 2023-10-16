#pragma once
#include "raylib.h"

class IInteraction
{
public:
	virtual void OnHovered() = 0;
	virtual void OnEndHovered() = 0;
	virtual void OnClicked() = 0;

	virtual Vector3 GetPosInGrid() = 0;

};

