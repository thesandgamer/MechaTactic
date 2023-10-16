#pragma once
#include "raylib.h"

class FX_Sprite
{
public:
	FX_Sprite();
	FX_Sprite(Texture2D image,int NumberOfFrames,float speed, Vector3 pos);
	~FX_Sprite();

	void Init();
	void Update();
	void Draw();


private:

	Texture2D sprite;

	Vector2 posOnScreen{0,0};

	int NbFrames{ 2 };


	Rectangle frameRec;


	int framesCounter{ 0 };
	int framesSpeed{ 8 };

	int currentFrame{ 0 };

	bool active{ true };

};

