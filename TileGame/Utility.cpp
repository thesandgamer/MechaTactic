#include "Utility.h"

void Utility::Start()
{
	champiTexture = LoadTexture("Ressources/ChampiColor.png");
	treeTexture = LoadTexture("Ressources/TreeMechColor.png");

	ChampiModel = LoadModel("Ressources/MechMush.glb");
	TreeModel = LoadModel("Ressources/MechTree.glb");
}

void Utility::Unload()
{
	UnloadTexture(champiTexture);
	UnloadModel(ChampiModel);

	UnloadTexture(treeTexture);
	UnloadModel(TreeModel);


}
