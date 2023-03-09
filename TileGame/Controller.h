#pragma once
#include "raylib.h"
#include <vector>
using std::vector;

#include "Button.h"
#include "MechaParent.h"

class Controller : public ITurn
{
	friend class PlayerController;

public:
	Controller();
	~Controller();

	void Start();
	void InitPawns();
	void Update();
	void Draw();
	void DrawUi();

	bool MoveMecha(Vector2 moveTo);//bool to check if the movement is possible

	bool SelectMecha(MechaParent* pawnSelected);
	void DeSelectMecha();

	vector<MechaParent>* GetMechas();
	vector<MechaParent> GetMechasDirect();

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
	vector<MechaParent> mechasList;
	MechaParent* controledMecha;

	class Grid* gridRef;

	//==========

	//==========
	bool isTurn = false;

	//==========UI==========



};
