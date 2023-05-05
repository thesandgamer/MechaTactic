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
	if (!isTurn) return;

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

}

void Controller::AddMecha(Vector3 location)
{
	mechasList.push_back(new MechaParent(location));
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
			gridRef->grid[pos.x][pos.y].ChangeColor(YELLOW);
		}

		//Faire en sorte que la couleur ne se garde pas
	}
	else
	{ 
		gridRef->ResetTilesColor();
	}
}

bool Controller::MoveMecha(Vector3 moveTo)
{
	controledMecha->MoveTo(moveTo);
	DeSelectMecha();
	gridRef->ResetTilesColor();
	return true;

	/*
	if (gridRef->grid[moveTo.x][moveTo.y].traversible == true)//Si la case séléctionné est traversible
	{
		
	}
	else
	{
		return false;
	}*/

}

bool Controller::SelectMecha(MechaParent* pawnSelected)
{
	if (controledMecha != nullptr) DeSelectMecha();
	controledMecha = pawnSelected;
	pawnSelected->selected = true;
	return false;
}

void Controller::DeSelectMecha()
{
	if (controledMecha != nullptr)
	{
		controledMecha->selected = false;
		controledMecha = nullptr;
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
		mecha->haveDoActions = false;
	}
	isTurn = true;
}

bool Controller::HaveEndTurn()
{
	return finishHisTurn;
}
