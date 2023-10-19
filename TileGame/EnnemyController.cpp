#include "EnnemyController.h"
#include "Game.h"

EnnemyController::EnnemyController(): Controller()
{
	name = "Ennemy";

}

EnnemyController::~EnnemyController()
{
}

void EnnemyController::Start()
{

	
	for (auto i = mechasList.begin(); i != mechasList.end(); i++)
	{
		(*i)->SetBaseColor({ 240,45,45,255 });	//Si on met plus de 255 comment �a marque erreur
	}

	Controller::Start();
}

void EnnemyController::Update()
{
	Controller::Update();

	if (!isTurn) return;

	if (controledMecha != nullptr)
	{
		if (controledMecha->haveMove)
		{
			AIActions();
		}
	}
	/*
	for (MechaParent* mech : mechasList)
	{
		if (!mech->haveDoActions)
		{
			break;
		}
		FinishTurn();

	}*/
	//FinishTurn();
}

void EnnemyController::StartTurn()
{
	Controller::StartTurn();
	it = 0;
	AIActions();

}		

/// <summary>
/// Do only once
/// </summary>
void EnnemyController::AIActions()
{
	DeSelectMecha();
	//++ToDo: changer pour que les m�chas s'activent un apr�s l'autre
	//if (it != 0 && it < mechasList.size()) it++;

	if (it >= mechasList.size())
	{
		FinishTurn();
		return;
	}

	SelectMecha(mechasList.at(it++));
	Vector2 PosToMove{};


	//Si case bloqu� check celles � cot�
	//V�rifier les cases � cot�, si toutes bloqu� refait du random
	do
	{
		float xGrid = std::rand() % (int)(gridRef->GRID_SIZE.x);//Random entre 0 et tailled de la grille
		float YGrid = std::rand() % (int)(gridRef->GRID_SIZE.z);//Random entre 0 et tailled de la grille
		PosToMove = { xGrid,YGrid };
	} while ((Game::instance().somethingAlreadyHere(PosToMove)));

	MoveMecha({ PosToMove.x,0,PosToMove.y });

	
}


//
// IA d�bile pour montrer que �a marche
// S�l�ctionne un m�cha au hazard dans la liste de ses m�chas
// S�l�ctionne une case, v�rifie si elle est vide, 
//	si elle l'est: move le mech vers cette case et finit son tour quand arriv�
//	sinon cherche une ature case
//