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

	Transform GetTransform() { return transform; }
	Transform* GetTransformPointer() { return &transform; }

	void SetPosition(Vector3 newPos) { transform.translation = newPos; }
	Vector3 GetPosition() { return transform.translation; }

	Vector3 GetPosInGrid() { return posInGrid; }


protected:
	Transform transform{ {-1,-1,-1},{0,0,0}, {1,1,1} };
	Vector3 posInGrid{ 0,0,0 };


};

