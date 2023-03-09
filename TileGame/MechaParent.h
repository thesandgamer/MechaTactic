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


enum class MechaState
{
	NORMAL,
	SelectedGhost,
	NoActionsPossible,
	Destroyed,
};


class MechaParent : public IInformationPasseur, public Actor
{
public:
	MechaParent();
	MechaParent(Vector3 positionP);
	MechaParent(Vector3 positionP, Model modelP);
	~MechaParent();

	void Init();
	void Draw();
	void Update();

	void DrawVisual();

	Vector3 GetLocation() { return transform.translation; }

	void MoveTo(Vector2 positionToGo);


	//========]	Informations
	InformationDisplay* GetInformations() { return informations; }
	void SetInformations(string newInfo) { info = newInfo; }

	string GetInformationOf() override;


	bool selected = false;
	bool haveDoActions = false;

	/*
	MechaParent(const MechaParent& other)
	{
		operator=(other);
	}


	MechaParent& operator=(const MechaParent& other)
	{
		this->position = other.position;
		this->width = other.width;
		this->height = other.height;
		this->gridRef = other.gridRef;
		this->informations = other.informations;
		this->sprite = other.sprite;
		return *this;
	}*/




private:
	Transform transform{ {0,0,0},{0,0,0},{1,1,1} };

	MechaState state{MechaState::NORMAL};
	InformationDisplay* informations{nullptr};
	string info;
	bool canMove = false;

	Model model{};


	//-------For A*--------
	std::vector<Vector2> poses{ };//Position où aller pour le A*


	//--------Variables for easing------------
	int currentTime = 0; //Variable utilisé pour l'easing
	int positionIterator = 0;
	int duration = 40;



};

