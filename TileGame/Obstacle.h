#pragma once
#include "Actor.h"	
#include "IInformationPasseur.h"
#include "InformationDisplay.h"
#include "BoxCollision.h"
#include "Grid.h"

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

	Vector3 GetPosInGrid() { return posInGrid; }


	Grid* refToGrid{  nullptr };

private:
	

	InformationDisplay* informations;
	string info;

	//-------Collisions-------
	BoxCollision collision{};

	//-------For drawing-------
	Model model{};

	Color drawColor{ WHITE };

};

