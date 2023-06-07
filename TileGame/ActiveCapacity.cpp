#include "ActiveCapacity.h"

#include "MechaParent.h"
#include "Controller.h"

//++ToDo: afficher la capacité active seulement quand elle est séléctionné

ActiveCapacity::ActiveCapacity(MechaParent& mech) : linkToMech(mech)
{
	Init();
}

void ActiveCapacity::Init()
{
	//++ToDo: rajouter un numéro genre 6 pour dire qu'on prend en compte la case du mécha	
	possibleZone = {
		{1,1,1,0,0},
		{0,0,1,0,0},
		{0,0,5,1,0},
		{0,0,1,1,1},
		{0,1,0,0,0},
		{0,0,1,1,0},

	};

	/*
	possibleZone = {
		{0,1,0,1,0},
		{1,1,1,1,1},
		{0,1,5,1,0},
		{1,1,1,1,1},
		{0,1,0,1,0},

	};*/


	button.textInButton = "Cap1";
	button.AddFunctionToTrigger(std::bind(&ActiveCapacity::ButtonClicked, this));
	button.AddHoverFunction(std::bind(&ActiveCapacity::DrawPossibleZone, this));
	button.lever = true;

}

void ActiveCapacity::Draw()
{
	linkToMech.gridRef->ResetTilesColor();

	if (!isActive) return;
	DrawPossibleZone();

}

void ActiveCapacity::Update()
{
	if (!isActive) return;

}

void ActiveCapacity::DrawUi()
{

}

void ActiveCapacity::DrawPossibleZone()
{
	SetPossibleZoneInGrid();
	for  (Vector2 var : possibleZoneInGrid)
	{
		if (linkToMech.gridRef->GetTile(var.x, var.y) != nullptr)
		{
			linkToMech.gridRef->GetTile(var.x, var.y)->ChangeColor(RED);
		}
	}
	
}

void ActiveCapacity::ButtonClicked()
{
	if (isActive) DeselectCapacity();
	else SelectCapacity();
}

void ActiveCapacity::SelectCapacity()
{
	isActive = true;
	linkToMech.SetCurrentActiveCapacity(this);
	linkToMech.SetState(MechaState::MODE_CAPACITY);
	//++ToDo: un event écouté par le controller qui déteient le mecha, pour dire passer en state capacité active séléctionnée
}

void ActiveCapacity::DeselectCapacity()
{
	isActive = false;
	linkToMech.gridRef->ResetTilesColor();
	linkToMech.SetCurrentActiveCapacity(nullptr);
	linkToMech.SetState(MechaState::SELECTED);
	button.UnPressButton();
}

bool ActiveCapacity::InPossibleZone(Vector2 pos)
{
	SetPossibleZoneInGrid();
	for (Vector2 i : possibleZoneInGrid)
	{
		if (i.x == pos.x && i.y == pos.y)
		{
			return true;
		}
	}
	return false;
}

void ActiveCapacity::SetPossibleZoneInGrid()
{
	possibleZoneInGrid.clear();

	Vector2 pos = { linkToMech.GetPosInGrid().x,linkToMech.GetPosInGrid().z };
	Vector2 mechaPosInGraph = { possibleZone.size() / 2,possibleZone.size() / 2 };

	for (int yy = 0; yy < possibleZone.size(); yy++)
	{
		for (int xx = 0; xx < possibleZone.at(yy).size(); xx++)
		{
			if (possibleZone.at(yy).at(xx) == 5)
			{
				mechaPosInGraph.x = xx;
				mechaPosInGraph.y = yy;
				break;
			}
		}
	}

	for (size_t yy = 0; yy < possibleZone.size(); yy++)
	{
		for (size_t xx = 0; xx < possibleZone.at(yy).size(); xx++)
		{

			if (possibleZone.at(yy).at(xx) == 5) continue;	//Si c'est la case d'origine

			if (possibleZone.at(yy).at(xx) == 1 || possibleZone.at(yy).at(xx) == 6)	//6 = self
			{
				int originX = pos.x - ((mechaPosInGraph.x));
				int originY = pos.y - ((mechaPosInGraph.y));

				Vector2 posInGrid = { originX + xx ,originY + yy };

				if (posInGrid.x >= 0 && posInGrid.x < linkToMech.gridRef->grid.size() && //If in grid with
					posInGrid.y >= 0 && posInGrid.y < linkToMech.gridRef->grid.at(yy).size())	//If in grid height
				{
					possibleZoneInGrid.push_back(posInGrid);
				}
			}
		}
	}

}

void ActiveCapacity::ActivateCapacity(Actor* actorTarget)
{
	//Fait l'effet de la capacité
	std::cout << "Capacity is activated" << std::endl;
	DeselectCapacity();//The mech no longer have capacity selected

	linkToMech.GetOwner()->DeSelectMecha();	//The controller no longer have the mech selected

	linkToMech.SetState(MechaState::INCAPACITY);//The mech is now on capacity state



	FinishCapacity();

}

void ActiveCapacity::FinishCapacity()
{
	linkToMech.EndAction();
}


void ActiveCapacity::DrawButton(Vector2 pos)
{
	button.Update();
	button.Draw();
}
