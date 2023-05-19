#include "EnnemyController.h"


EnnemyController::EnnemyController(): Controller()
{
}

EnnemyController::~EnnemyController()
{
}

void EnnemyController::Start()
{
	name = "Ennemy";
	for (auto i = mechasList.begin(); i != mechasList.end(); i++)
	{
		(*i)->SetBaseColor({ 240,45,45,255 });	//Si on met plus de 255 comment ça marque erreur
	}

	Controller::Start();
}

void EnnemyController::Update()
{
	if (!isTurn) return;

	Controller::Update();

	if (controledMecha != nullptr)
	{
		if (controledMecha->haveDoActions)
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
	//++ToDo: changer pour que les méchas s'activent un après l'autre
	//if (it != 0 && it < mechasList.size()) it++;

	if (it >= mechasList.size())
	{
		FinishTurn();
		return;
	}

	SelectMecha(mechasList.at(it++));

	float xGrid = std::rand() % (int)(gridRef->GRID_SIZE.x);//Random entre 0 et tailled de la grille
	float YGrid = std::rand() % (int)(gridRef->GRID_SIZE.z);//Random entre 0 et tailled de la grille
	Vector2 PosToMove{ xGrid,YGrid };

	//Vérifier les cases à coté, si toutes bloqué refait du random

	while ((PosToMove.x == controledMecha->GetPosInGrid().x && PosToMove.y == controledMecha->GetPosInGrid().z)
		//|| (  SomethingAlreadyHere(PosToMove))	// à rajouter check si pas quelque chose déjà ici
		)
	{
		float xGrid = std::rand() % (int)(gridRef->GRID_SIZE.x);//Random entre 0 et tailled de la grille
		float YGrid = std::rand() % (int)(gridRef->GRID_SIZE.z);//Random entre 0 et tailled de la grille
		PosToMove = { xGrid,YGrid };
	}

	MoveMecha({ PosToMove.x,0,PosToMove.y });

	
}


//
// IA débile pour montrer que ça marche
// Séléctionne un mécha au hazard dans la liste de ses méchas
// Séléctionne une case, vérifie si elle est vide, 
//	si elle l'est: move le mech vers cette case et finit son tour quand arrivé
//	sinon cherche une ature case
//