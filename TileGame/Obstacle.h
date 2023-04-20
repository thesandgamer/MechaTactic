#pragma once
#include "Actor.h"	
#include "IInformationPasseur.h"
#include "InformationDisplay.h"

class Obstacle: public Actor, public IInformationPasseur
{
public:
	Obstacle();
	Obstacle(Vector3 positionP);
	~Obstacle() {};


	void Init() override;
	void Draw() override;
	void Update() override;

	InformationDisplay* GetInformations() { return informations; }
	void SetInformations(string newInfo) { info = newInfo; }

	string GetInformationOf() override;


private:
	InformationDisplay* informations;
	string info;

};

