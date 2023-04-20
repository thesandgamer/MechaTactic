#include "Tile.h"
#include "Grid.h"

Tile::Tile(): refToGrid{nullptr}, informations{nullptr}
{

}

Tile::Tile(Vector3 positionP): Actor()
{
	posInGrid = positionP;
}

Tile::Tile(Vector3 positionP, Model modelP) : model{ modelP }, Actor()
{
	posInGrid = positionP;
}


void Tile::Init()
{
	//-------Set collision
	collision = BoxCollision(&model);
	collision.SetParent(&transform);
	collision.id = "TileCollision";

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
	posInGridToPos();



}

void Tile::Draw()
{

	DrawModel(model, transform.translation, transform.scale.x, drawColor);
}

void Tile::Update()
{
}


string Tile::GetInformationOf()
{
	string info = "    --Tile de Sol-- \nPas d'effet particulier";
	informations->SetTitle(info);

	return info;
}

void Tile::posInGridToPos()
{
	transform.translation = refToGrid->PosInGridToPosToWorld(posInGrid);

}
