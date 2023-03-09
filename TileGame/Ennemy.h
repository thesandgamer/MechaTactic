#pragma once
#include "raylib.h"
#include <vector>
using std::vector;

#include "Button.h"
#include "Pawn.h"

class Ennemy : public ITurn
{
public:
	Ennemy();
	~Ennemy();

	void Start();
	void Update();
	void Draw();

	vector<Pawn>* GetPawns();


	void SetGrid(class Grid* grid);

	void FinishEnnemyTurn();


	//==========Interfaces==========
	void StartTurn();
	bool HaveEndTurn();
	int initiative;
	bool finishHisTurn = false;

	string GetName() { return name; }
	string name;


private:
	vector<Pawn> pawns;
	Pawn* controledPawn;

	class Grid* gridRef;


	bool isTurn = false;
};

