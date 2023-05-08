#include "ActiveCapacity.h"

#include "MechaParent.h"


ActiveCapacity::ActiveCapacity(MechaParent& mech) : linkToMech(mech)
{
	Init();
}

void ActiveCapacity::Init()
{
	/*
	possibleZone = {
		{0,0,1,0,0},
		{0,0,1,0,0},
		{1,1,5,1,1},
		{0,0,1,0,0},
		{0,0,1,0,0},

	};*/
	possibleZone = {
		{0,1,0,1,0},
		{1,1,1,1,1},
		{0,1,5,1,0},
		{1,1,1,1,1},
		{0,1,0,1,0},

	};
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
				int a = 0;
				if (mechaPosInGraph[0] == 0){
					a = (mechaPosInGraph[0] == 0) ? 1 : 0;
				}
				if(mechaPosInGraph[0] >= possibleZone.capacity()-1){
					a = (mechaPosInGraph[0] > possibleZone.capacity()-1) ? 0 : 1;
				}

				int b = 0;
				if (mechaPosInGraph[1] == 0){
					b = (mechaPosInGraph[1] == 0) ? 1 : 0;
				}
				if(mechaPosInGraph[1] >= possibleZone.at(xx).capacity()-1) {
					b = (mechaPosInGraph[1] > possibleZone.at(xx).capacity()-1) ? 0 : 1;
				}


				if (linkToMech.gridRef->GetTile(pos.x/ (mechaPosInGraph[0]+ a ) + xx, pos.y/ (mechaPosInGraph[1]+ b) + yy) != nullptr)
				{	
					linkToMech.gridRef->GetTile(pos.x/ (mechaPosInGraph[0]+ a ) + xx, pos.y/ (mechaPosInGraph[1]+ b) + yy)->ChangeColor(RED);
				}
			}
		}
	}
}
