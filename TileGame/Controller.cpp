#include "Controller.h"

#include "Grid.h"


Controller::Controller() : controledMecha{ nullptr }, gridRef{ nullptr }
{
	name = "Generic Controller";
}

Controller::~Controller()
{
}

void Controller::Start()
{
	//=========Gère les pawns============
	std::cout << "		Controller " << name << " have started" << std::endl;
	InitPawns();
}

void Controller::InitPawns()
{
	for (int i = 0; i < mechasList.size(); i++)
	{
		mechasList.at(i)->Init();
	}
}

void Controller::Update()
{
	//if (!isTurn) return;

	//==========Update les pawns============
	for (int i = 0; i < mechasList.size(); i++)
	{
		mechasList.at(i)->Update();
	}
}

void Controller::Draw()
{
	//=========Draw les pawns============

	for (int i = 0; i < mechasList.size(); i++)
	{
		mechasList.at(i)->Draw();
	}
}

void Controller::DrawUi()
{
	//if (!isTurn) return;
	for (auto i = mechasList.begin(); i < mechasList.end(); i++)
	{
		(*i)->DrawUI();
	}

}

void Controller::AddMecha(MechaParent* mech)
{
	//++ToDo: check si on peut ajouter le mécha à cette position utiliser assertion
	mechasList.push_back(mech);
	mechasList.back()->SetOwner(this);
}

/// <summary>
/// Function pour mettre en éviedence le chemin entre le mécha selectionné et une position
/// </summary>
/// <param name="end"></param>
void Controller::ShowPath(Vector3 end)
{
	//++ToDo: faire en sorte que ça dessine plus un trait entre de tile en tile
	if (controledMecha != nullptr)
	{
		gridRef->ResetTilesColor();
		//Fait path entre mecha selectionné et position
		std::vector<Vector2> poses = gridRef->aStar.GetPath({ controledMecha->GetPosInGrid().x,controledMecha->GetPosInGrid().z }, { end.x,end.z });

		for (Vector2 pos : poses)
		{
			gridRef->grid[pos.x][pos.y].ChangeColor(BLUE);
		}

		//Faire en sorte que la couleur ne se garde pas
	}
	else
	{ 
		gridRef->ResetTilesColor();
	}
}

bool Controller::IsCurrentMechInAction()	//marche pas car controlled mecha est reset quand on l'active
{
	if (controledMecha != nullptr)	//Si on à un mécha selectionné
	{
		if (controledMecha->GetState() == MechaState::INMOVEMENT 
			|| controledMecha->GetState() == MechaState::INCAPACITY)	//Si il ne fait rien
		{
			//cState = MechaMakeActions;
			return true;
		}
		return false;	//Le mecha ne fait rien
	}
	return false;	//Il n'y a pas de mecha selectionné
}

void Controller::MoveMecha(Vector3 moveTo)
{
	controledMecha->MoveTo(moveTo);
	gridRef->ResetTilesColor();//To remove the show path

	//DeSelectMecha();
	/*
	if (gridRef->grid[moveTo.x][moveTo.y].traversible == true)//Si la case séléctionné est traversible
	{
		
	}
	else
	{
		return false;
	}*/

}

/// <summary>
/// I think to remove this but i'm not sure
/// </summary>
/// <param name="pawnSelected"></param>
/// <returns></returns>
bool Controller::SelectMecha(MechaParent* pawnSelected)
{
	if (controledMecha != nullptr) DeSelectMecha();

	controledMecha = pawnSelected;
	pawnSelected->Select();
	cState = MechaSelected;

	return true;
}

void Controller::DeSelectMecha()
{
	if (controledMecha != nullptr)
	{
		controledMecha->DeSelect();
		controledMecha = nullptr;
		cState = Thinking;
		gridRef->ResetTilesColor();

	}

}

/*
vector<MechaParent*>* Controller::GetMechas()
{
	return &mechasList;
}

vector<MechaParent*> Controller::GetMechasDirect()
{
	return mechasList;
}*/

void Controller::SetGrid(Grid* grid)
{
	gridRef = grid;
}

void Controller::FinishTurn()
{
	isTurn = false;
	finishHisTurn = true;
}



void Controller::StartTurn()
{
	std::cout << "Its " << name <<" Turn " << std::endl;
	finishHisTurn = false;

	for (MechaParent* mecha : mechasList)
	{
		mecha->StartTurn();
	}
	isTurn = true;
}

bool Controller::HaveEndTurn()
{
	return finishHisTurn;
}
