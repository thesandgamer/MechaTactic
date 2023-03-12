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
	std::cout << "		Controller " << name << " have stated" << std::endl;
	InitPawns();
}

void Controller::InitPawns()
{
	for (int i = 0; i < mechasList.size(); i++)
	{
		mechasList.at(i).Init();
	}
}

void Controller::Update()
{
	if (!isTurn) return;

	//==========Update les pawns============
	for (int i = 0; i < mechasList.size(); i++)
	{
		mechasList.at(i).Update();
	}
}

void Controller::Draw()
{
	//=========Draw les pawns============

	for (int i = 0; i < mechasList.size(); i++)
	{
		mechasList.at(i).Draw();
	}
}

void Controller::DrawUi()
{

}

void Controller::AddMecha(Vector3 location)
{
	mechasList.push_back(MechaParent(location));
}


bool Controller::MoveMecha(Vector2 moveTo)
{
	if (gridRef->grid[moveTo.x][moveTo.y].traversible == true)//Si la case séléctionné est traversible
	{
		//std::cout << "traversible" << std::endl;
		controledMecha->MoveTo({ moveTo.x, moveTo.y });
		DeSelectMecha();
		return true;
	}
	else
	{
		return false;
	}

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

vector<MechaParent>* Controller::GetMechas()
{
	return &mechasList;
}

vector<MechaParent> Controller::GetMechasDirect()
{
	return mechasList;
}

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

	for (MechaParent& mecha : mechasList)
	{
		mecha.haveDoActions = false;
	}
	isTurn = true;
}

bool Controller::HaveEndTurn()
{
	return finishHisTurn;
}
