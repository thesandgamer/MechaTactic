#pragma once
#include "raylib.h"
#include <vector>
using std::vector;

#include "Button.h"
#include "MechaParent.h"



enum ControllerState
{
	Thinking,	//State où aucun mécha n'est séléctionné
	MechaSelected,	//Un mecha est séléctionné
	MechaMoveSelected,	
	MechaCapacitySelected,
	MechaMakeActions,	//Un mecha fait ses actions
};

class Controller : public ITurn
{

public:
	Controller();
	~Controller();

	virtual void Start();
	virtual void Update();
	virtual void Draw();
	virtual void DrawUi();

	void AddMecha(Vector3 location);

	bool MoveMecha(Vector3 moveTo);//bool to check if the movement is possible


	bool SelectMecha(MechaParent* pawnSelected);
	void DeSelectMecha();


	//vector<MechaParent*>* GetMechas();
	//vector<MechaParent*> GetMechasDirect();

	int GetNumberOfMechas() { return mechasList.size(); }
	MechaParent* GetMechaAt(int index) { return mechasList.at(index); }

	void SetGrid(class Grid* grid);


	void FinishTurn();

	MechaParent* GetControledPawn() { return controledMecha; }


	//==========Interfaces==========
	void StartTurn();
	bool HaveEndTurn();

	int initiative;
	bool finishHisTurn = false;

	string GetName() { return name; }
	string name;


protected:

	void ShowPath(Vector3 end);

	bool IsCurrentMechInAction();

	//======] For Mechas
	void InitPawns();

	vector<MechaParent*> mechasList{};	//*Remplacer par smart pointer: unique pointers
	MechaParent* controledMecha{ nullptr };	//Juste un lien vers le mecha

	//======] Grid
	class Grid* gridRef{nullptr};	//Juste un lien vers la grille: juste une référence

	//======] State
	ControllerState cState {Thinking};

	bool isTurn{false};

	//======] UI

};
