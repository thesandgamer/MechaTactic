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


/*	//++ToDo:

	M�cha: 
		Pour la s�l�ction de son action
	en mode d�placement de base
	Mode d�placement:
		Quand on survolle une tile acessible, montre le chemin actuel/ possible
	Mode Capacit�:
		Montre zone possible


	Mode effectue la capacit�e: perte du controller du contr�le sur le mecha


	Capacit�?
	Affichage � l'�cran quand le mecha est selectionn�
	Affiche les boutons:
		Quand on clique sur le bouton, le bouton est selectionn�, et la capacit� aussi
		Si on clique sur un autre bouton le bouton selectionn� pr�c�dement se d�s�l�ctionne, et la capacit� de m�me 


	Faire un reset du mecha (actif, capacti� selectionn�,...) 


*/


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

	void MoveTo(Vector3 positionToGo);


	//========]	Informations

	InformationDisplay* GetInformations() { return informations; }
	void SetInformations(string newInfo) { info = newInfo; }

	string GetInformationOf() override;

	//========] Interaction

	void OnHovered() override;
	void OnClicked() override;

	Vector3 GetPosInGrid() { return posInGrid; }



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

	//++ToDo: Limiter le d�placement des mechas et afficher au sol o� il peut se d�placqer


private:
	Vector3 posInGrid { 0,0,0 };

	Grid* gridRef;	//Juste un lien vers la grille

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

