#pragma once
#include <iostream> 
#include "raylib.h"
#include "easings.h"

#include "Actor.h"

#include "Grid.h"
#include "Vector2AStar.h"
#include "InformationDisplay.h"
#include "IInformationPasseur.h"
#include "ITurn.h"




class Pawn: public IInformationPasseur, public Actor
{
public:
	Pawn();
	Pawn(Vector2 positionP);
	Pawn(Vector2 positionP, Texture2D spriteP);
	Pawn(Vector2 positionP,float widthP,float heightP);
	~Pawn();

	void Init() ;
	void Draw() ;
	void Update() ;

	void DrawVisual(Vector2 positionP, bool ghost);
		
	//Vector2 position;

	float width;
	float height;

	void MoveTo(Vector2 positionToGo);

	InformationDisplay* GetInformations() { return informations; }
	void SetInformations(string newInfo) { info = newInfo; }

	string GetInformationOf() override;


	bool selected = false;

	bool haveDoActions = false;


	Pawn(const Pawn& other)
	{
		operator=(other);
	}

	Pawn& operator=(const Pawn& other)
	{
		this->position = other.position;
		this->width = other.width;
		this->height = other.height;
		this->gridRef = other.gridRef;
		this->informations = other.informations;
		this->sprite = other.sprite;
		return *this;
	}

	//=====Couleurs
	Color col = YELLOW;
	Color selCol = RED;


private:
	InformationDisplay* informations;
	string info;
	bool canMove = false;
	



};

