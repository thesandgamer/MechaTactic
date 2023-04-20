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
#include "IInteraction.h"

#include "BoxCollision.h"


//++ToDo: Pousser l'utilisation de la machine d'�tat 
enum class MechaState
{
	NORMAL,
	Selected,
	SelectedGhost,
	NoActionsPossible,
	Destroyed,
};


class MechaParent : public IInformationPasseur, public Actor, public IInteraction
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

	//========] Interaction

	void OnHovered() override;
	void OnClicked() override;


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

	void SetBaseColor(Color color) { baseColor = color; }


private:
	Vector3 posInGrid { 0,0,0 };

	Grid* gridRef;

	BoxCollision collision{};

	MechaState state {MechaState::NORMAL};

	InformationDisplay* informations{nullptr};
	string info;
	bool canMove = false;


	//-------For drawing-------
	Model model{};

	Color drawColor {WHITE};
	Color baseColor {PURPLE};




	//-------For A*--------
	std::vector<Vector2> poses{ };//Position o� aller pour le A*


	//--------Variables for easing------------
	int currentTime = 0; //Variable utilis� pour l'easing
	int positionIterator = 0;
	int duration = 40;



};

