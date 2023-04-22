#pragma once
#include "raylib.h"
#include <vector>
using std::vector;

#include "Button.h"
#include "MechaParent.h"

enum ControllerState
{
	Thinking,
	MechaSelected,
	MechaMakeActions,
};

class Controller : public ITurn
{

public:
	Controller();
	~Controller();

	virtual void Start();
	void InitPawns();
	virtual void Update();
	virtual void Draw();
	virtual void DrawUi();

	void AddMecha(Vector3 location);

	bool MoveMecha(Vector3 moveTo);//bool to check if the movement is possible

	bool SelectMecha(MechaParent* pawnSelected);
	void DeSelectMecha();

	vector<MechaParent*>* GetMechas();
	vector<MechaParent*> GetMechasDirect();

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
	vector<MechaParent*> mechasList{};	//Pointeurs car on veut pouvoir mettre des enfants
	MechaParent* controledMecha{ nullptr };

	class Grid* gridRef{nullptr};

	//==========
	ControllerState cState {Thinking};

	//==========
	bool isTurn{false};

	//==========UI==========



};
