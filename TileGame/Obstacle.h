#pragma once
#include "Actor.h"	

class Obstacle: public Actor, public IInformationPasseur
{
public:
	Obstacle();
	Obstacle(Vector2 positionP, Texture2D spriteP);
	~Obstacle() {};

	void Draw();

	InformationDisplay* GetInformations() { return informations; }
	void SetInformations(string newInfo) { info = newInfo; }

	string GetInformationOf() override;


private:
	InformationDisplay* informations;
	string info;

};

