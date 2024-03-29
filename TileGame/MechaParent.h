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

#include "LifeManager.h"
#include "InGameLifeBar.h"

//++ToDo: Pousser l'utilisation de la machine d'�tat 
//++ToDo: Remplacer la state machine par des flags: Hover Selected CanMove CanUseCapacity InMovement InCapacity

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

class Controller;

//++ToDo: Ajouter une classe pour l'interface

/*	//++ToDo:

	M�cha: 
		Pour la s�l�ction de son action
	en mode d�placement de base
	V Mode d�placement:
		V Quand on survolle une tile acessible, montre le chemin actuel/ possible
	V Mode Capacit�:
		V Montre zone possible


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
	void OnEndHovered()override;
	void OnClicked() override;

	Vector3 GetPosInGrid() { return posInGrid; }


	//
	void Select();
	void DeSelect();

	bool IsSelected() { return selected; }



	bool haveDoActions = false;
	bool haveMove = false;

	bool CanBeActivate();

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

	//++ToDo: Limiter le d�placement des mechas et afficher au sol o� il peut se d�placqer


	Grid* gridRef{ nullptr };	//Juste un lien vers la grille

	void AddCapacity(std::unique_ptr<Capacity>&& newCapacity);	//&& r value

	ActiveCapacity* GetCurrentActiveCapacity();
	void SetCurrentActiveCapacity(ActiveCapacity* capacity);


	void SetOwner(Controller* newOwner) { owner = newOwner; }
	Controller* GetOwner() { return owner; }

	void EndMovement();
	void EndAction();

	LifeManager* GetLifeManager() { return &lifeManager; }

	void Destroy();


protected:

	bool selected{ false };

	//std::vector<Capacity*> capacities;	//Comment mettre un unique ptr ici?
	std::vector<std::unique_ptr<Capacity>> capacities;
	ActiveCapacity* currentActiveCapacity;	//Pointer car besoin de savoir si c'est null

	//void ManagerCapacities();
	Controller* owner { nullptr };	//++ToDo: Peut �tre remplacer �a par un interface de ownership de mechs

	LifeManager lifeManager{this, 3,0 };
	InGameLifeBar lifeBar{ this ,&lifeManager, { 0,60,0 } };
	
	bool canDrawLifeBar{ false };



	BoxCollision collision{ {32,32,32} };

	MechaState state {MechaState::IDLE};

	InformationDisplay* informations{nullptr};
	string info;
	bool canMove = false;


	//-------For drawing-------
	Model model{};
	Texture2D texture{};

	Color drawColor {WHITE};
	Color baseColor {PURPLE};



	//-------For A*--------
	std::vector<Vector2> poses{ };//Position o� aller pour le A*


	//--------Variables for easing------------
	int currentTime = 0; //Variable utilis� pour l'easing
	int positionIterator = 0;
	int duration = 40;

	void MakeMovement();



};

