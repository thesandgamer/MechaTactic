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
	//=========G�re les pawns============
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
	if (!isTurn) return;

}

void Controller::AddMecha(Vector3 location)
{
	mechasList.push_back(new MechaParent(location));
}

/// <summary>
/// Function pour mettre en �viedence le chemin entre le m�cha selectionn� et une position
/// </summary>
/// <param name="end"></param>
void Controller::ShowPath(Vector3 end)
{
	//++ToDo: faire en sorte que �a dessine plus un trait entre de tile en tile
	if (controledMecha != nullptr)
	{
		gridRef->ResetTilesColor();
		//Fait path entre mecha selectionn� et position
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

bool Controller::IsCurrentMechInAction()
{
	if (controledMecha != nullptr)	//Si on � un m�cha selectionn�
	{
		if (controledMecha->GetState() == MechaState::INMOVEMENT 
			&& controledMecha->GetState() == MechaState::INCAPACITY)	//Si il ne fait rien
		{
			return true;
		}
		return false;	//Le mecha ne fait rien
	}
	return false;	//Il n'y a pas de mecha selectionn�
}

bool Controller::MoveMecha(Vector3 moveTo)
{
	controledMecha->MoveTo(moveTo);

	//DeSelectMecha();

	gridRef->ResetTilesColor();//To remove the show path

	return true;

	/*
	if (gridRef->grid[moveTo.x][moveTo.y].traversible == true)//Si la case s�l�ctionn� est traversible
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
	pawnSelected->Select();

	return true;
}

void Controller::DeSelectMecha()
{
	if (controledMecha != nullptr)
	{
		controledMecha->DeSelect();
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
		mecha->StartTurn();
	}
	isTurn = true;
}

bool Controller::HaveEndTurn()
{
	return finishHisTurn;
}
