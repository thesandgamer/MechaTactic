#pragma once
#include "raylib.h"

class Actor
{

public:

	Actor();
	~Actor();

	virtual void Init() {};
	virtual void Draw() {};
	virtual void Update() {};


	bool isActive = true;


protected:
	Transform transform;


};

