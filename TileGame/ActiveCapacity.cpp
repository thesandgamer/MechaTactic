#include "ActiveCapacity.h"

#include "MechaParent.h"


ActiveCapacity::ActiveCapacity(MechaParent& mech) : linkToMech(mech)
{
	Init();
}

void ActiveCapacity::Init()
{
	
	possibleZone = {
		{0,0,1,0,0},
		{0,5,1,0,0},
		{0,1,1,0,1},
		{0,0,1,0,0},
		{0,0,1,1,1},
		{0,0,0,0,1},

	};
	/*
	possibleZone = {
		{0,1,0,1,0},
		{1,1,1,1,1},
		{0,1,5,1,0},
		{1,1,1,1,1},
		{0,1,0,1,0},

	};*/
}

void ActiveCapacity::DrawPossibleZone()
{
	Vector2 pos = { linkToMech.GetPosInGrid().x,linkToMech.GetPosInGrid().z };
	int mechaPosInGraph[2] = {possibleZone.size() / 2,possibleZone.size() / 2};

	for (int xx = 0; xx < possibleZone.size(); xx++)
	{
		for (int yy = 0; yy < possibleZone.at(xx).size(); yy++)
		{
			if (possibleZone[xx][yy] == 5)
			{
				mechaPosInGraph[1] = xx; 
				mechaPosInGraph[0] = yy; 
				break;
			}
		}
	}
	//mechaPosInGraph[0] /= possibleZone.size();
	//mechaPosInGraph[1] /= possibleZone.at(0).size();

	for (size_t xx = 0; xx < possibleZone.size(); xx++)
	{
		for (size_t yy = 0; yy < possibleZone.at(xx).size(); yy++)
		{

			if (possibleZone[xx][yy] == 5) continue;	//Si c'est la case d'origine

			if (possibleZone[xx][yy] == 1)
			{
				/*
				//Check if the pos of the mecha in attack is on border
				int a = 0;
				if (mechaPosInGraph[0] == 0){
					a = 0;
				}
				if(mechaPosInGraph[0] >= possibleZone.capacity()-1){
					a = 1;
				}

				int b = 0;
				if (mechaPosInGraph[1] == 0){
					b = 1;
				}
				if(mechaPosInGraph[1] >= possibleZone.at(xx).capacity()-1) {
					b = 0;
				}

				int divX = std::ceil(mechaPosInGraph[0] + a);
				int divY = std::ceil(mechaPosInGraph[1] + b);
				*/

				//To have the origin where start puting mech
				//	L'origin = postion du mecha - (position du mecha dans le graph)
				int originX = pos.x - ((mechaPosInGraph[0]));
				int originY = pos.y - ((mechaPosInGraph[1]));

				if (linkToMech.gridRef->GetTile(originX + yy, originY + xx) != nullptr)
				{	
					linkToMech.gridRef->GetTile(originX + yy, originY + xx)->ChangeColor(RED);
				}
			}
		}
	}
}
