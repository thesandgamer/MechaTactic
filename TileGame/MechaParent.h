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

#include "Capacity.h"
#include "ActiveCapacity.h"

//++ToDo: Pousser l'utilisation de la machine d'état 
enum class MechaState
{
	IDLE,
	SELECTED,
	INMOVEMENT,
	INCAPACITY,
	DEACTIVATED,
	MODE_MOVE,
	MODE_CAPACITY,
};


/*	//++ToDo:

	Mécha: 
		Pour la séléction de son action
	en mode déplacement de base
	Mode déplacement:
		Quand on survolle une tile acessible, montre le chemin actuel/ possible
	Mode Capacité:
		Montre zone possible


	Mode effectue la capacitée: perte du controller du contrôle sur le mecha


	Capacité?
	Affichage à l'écran quand le mecha est selectionné
	Affiche les boutons:
		Quand on clique sur le bouton, le bouton est selectionné, et la capacité aussi
		Si on clique sur un autre bouton le bouton selectionné précédement se déséléctionne, et la capacité de même 


	Faire un reset du mecha (actif, capactié selectionné,...) 


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
	void DrawUI();
	void Update();

	void StartTurn();

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


	//
	void Select();
	void DeSelect();

	bool IsSelected() { return selected; }



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

	MechaState& GetState() { return state; }
	void SetState(MechaState newState) { state = newState; }

	//++ToDo: Limiter le déplacement des mechas et afficher au sol où il peut se déplacqer


	Grid* gridRef{ nullptr };	//Juste un lien vers la grille

	void AddCapacity(std::unique_ptr<Capacity>&& newCapacity);	//&& r value

	ActiveCapacity* GetCurrentActiveCapacity();
	void SetCurrentActiveCapacity(ActiveCapacity* capacity);

private:

	bool selected{ false };

	//std::vector<Capacity*> capacities;	//Comment mettre un unique ptr ici?
	std::vector<std::unique_ptr<Capacity>> capacities;	//Comment mettre un unique ptr ici?
	ActiveCapacity* currentActiveCapacity;	//Pointer car besoin de savoir si c'est null

	//void ManagerCapacities();


	Vector3 posInGrid { 0,0,0 };


	BoxCollision collision{};

	MechaState state {MechaState::IDLE};

	InformationDisplay* informations{nullptr};
	string info;
	bool canMove = false;


	//-------For drawing-------
	Model model{};

	Color drawColor {WHITE};
	Color baseColor {PURPLE};




	//-------For A*--------
	std::vector<Vector2> poses{ };//Position où aller pour le A*


	//--------Variables for easing------------
	int currentTime = 0; //Variable utilisé pour l'easing
	int positionIterator = 0;
	int duration = 40;

	void MakeMovement();



};

