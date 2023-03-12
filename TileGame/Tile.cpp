#include "Tile.h"
#include "Grid.h"

Tile::Tile(): refToGrid{nullptr}, informations{nullptr}
{

}

Tile::Tile(Vector3 positionP)
{
	transform.translation = positionP;
}

Tile::Tile(Vector3 positionP, Model modelP): model{modelP}
{
	transform.translation = positionP;
}


void Tile::Init()
{
	//-------Set collision
	collision = BoxCollision(&model);
	collision.SetParent(&transform);

	if (model.meshCount == NULL)//Si on à pas de mesh de loadé, load un cube
	{
		drawColor = PURPLE;
		model = LoadModelFromMesh(GenMeshCube(refToGrid->CELL_WIDTH, refToGrid->CELL_HEIGHT, refToGrid->CELL_WIDTH));
	}
	collision.Init();

	//-----Set les infos
	informations = new InformationDisplay();
	//informations->SetPos(&pos);
	informations->infPasseur = this;

	//------
	transform.translation = { transform.translation.x * refToGrid->CELL_WIDTH,transform.translation.y * refToGrid->CELL_WIDTH, transform.translation.z * refToGrid->CELL_HEIGHT };



}

void Tile::Draw()
{

	DrawModel(model, transform.translation, transform.scale.x, drawColor);
	collision.Draw();
}


string Tile::GetInformationOf()
{
	string info = "    --Tile de Sol-- \nPas d'effet particulier";
	informations->SetTitle(info);

	return info;
}
