#pragma once
#include "raylib.h"
#include <vector>
using std::vector;

#include "Button.h"
#include "Pawn.h"

/// <summary>
/// Juste une archive, plus utilisée
/// </summary>
class Player: public ITurn
{
	/*
public:
	Player();
	~Player();

	void Start();
	void Update();
	void Draw();
	void DrawUi();

	void MovePawn();

	bool SelectPawn();
	void DeSelectPawn();

	vector<Pawn>* GetPawns();
	vector<Pawn> GetPawnsDirect();

	void SetGrid(class Grid* grid);

	Vector2 GetMousePosInGrid() { return mousePosInGrid; }

	void FinishPlayerTurn();

	Pawn* GetControledPawn() { return controledPawn; }


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

//==========
	Vector2 mousePos;
	Vector2 mousePosInGrid;

//==========
	bool isTurn = false;

	Player* This;

//==========UI==========
	Button* endTurnButton = nullptr;



	*/
};

//C'est la classe qui va servir à gérer le joueur
//On va y stoquer les pawn qu'il possède
//On va stoquer le pawn qu'on contrôle actuèlement	


//On va aussi y stoquer son Ui