#pragma once
#include <raylib.h>
#include <iostream>
#include <string>
using std::string;

class BandeauTexte
{
public:
	BandeauTexte();
	BandeauTexte(Texture2D spriteP	,Vector2 positionP, float lifeTimeP);
	~BandeauTexte();

	void Update();
	void Draw();

	void DisplayBandeau();
	void SetText(string text);

private:
	float lifeTime;
	bool isActive;

	Vector2 position;

	Texture2D sprite;

	string textIn;
};

