#include "Ennemy.h"

Ennemy::Ennemy()
{
	name = "Ennemy";

}

Ennemy::~Ennemy()
{
}

void Ennemy::Start()
{

//=========
	Texture2D mech1Sprite = LoadTexture("Ressources/MechRed1.png");
	Texture2D mech2Sprite = LoadTexture("Ressources/MechRed2.png");
	pawns.push_back(Pawn({ 7,0 }, mech1Sprite));
	pawns.push_back(Pawn({ 4,2 }, mech2Sprite));

	pawns.at(0).SetInformations("    ----Cylinder Ennemi Mech----\n");
	pawns.at(1).SetInformations("    ----Pyramid Ennemi Mech----\n");

	for (int i = 0; i < pawns.size(); i++)
	{
		pawns.at(i).col = PURPLE;
		pawns.at(i).selCol = DARKPURPLE;
		pawns.at(i).Init();
	}
}

float actualCounter = 0;

void Ennemy::Update()
{
	if (!isTurn) return;

	if (actualCounter < 5)
	{
		actualCounter += GetFrameTime();
	}
	else
	{
		actualCounter = 0;
		finishHisTurn = true;
	}

	//==========Update les pawns============
	for (int i = 0; i < pawns.size(); i++)
	{
		pawns.at(i).Update();
	}

}

void Ennemy::Draw()
{
	//=========Draw les pawns============
	for (int i = 0; i < pawns.size(); i++)
	{
		pawns.at(i).Draw();
	}
}

vector<Pawn>* Ennemy::GetPawns()
{
	return &pawns;
}

void Ennemy::SetGrid(Grid* grid)
{
	gridRef = grid;
}

void Ennemy::FinishEnnemyTurn()
{
	finishHisTurn = true;
}

void Ennemy::StartTurn()
{
	std::cout << "Its Ennemy Turn " << std::endl;
	for (Pawn& pawn : pawns)
	{
		pawn.haveDoActions = false;
	}
	isTurn = true;
	finishHisTurn = false;
}

bool Ennemy::HaveEndTurn()
{
	return finishHisTurn;
}
