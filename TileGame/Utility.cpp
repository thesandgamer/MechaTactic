#include "Utility.h"

void Utility::Start()
{
	champiTexture = LoadTexture("Ressources/ChampiColor.png");
	treeTexture = LoadTexture("Ressources/TreeMechColor.png");
	rockTexture = LoadTexture("Ressources/RockColor.png");

	ChampiModel = LoadModel("Ressources/MechMush.glb");
	TreeModel = LoadModel("Ressources/MechTree.glb");
	RockModel = LoadModel("Ressources/Rock.glb");
	CellModel = LoadModel("Ressources/Cell.glb");
}

void Utility::Unload()
{
	UnloadTexture(champiTexture);
	UnloadModel(ChampiModel);

	UnloadTexture(treeTexture);
	UnloadModel(TreeModel);

	UnloadTexture(rockTexture);
	UnloadModel(RockModel);

}
