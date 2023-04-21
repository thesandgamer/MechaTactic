#include "Tile.h"
#include "Grid.h"
#include "Game.h"

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
	collision.SetParent(this);
	collision.id = "TileCollision";

	if (model.meshCount == NULL)//Si on � pas de mesh de load�, load un cube
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
	if (posInGrid.x == 0 && posInGrid.z == 0)
	{
		drawColor = RED;
	}
	if (posInGrid.x == 9 && posInGrid.z == 9)
	{
		drawColor = RED;
	}

	DrawModel(model, transform.translation, transform.scale.x, drawColor);

	//Vector2 pos = GetWorldToScreen(transform.translation,*Game::instance().GetCamera());
	//DrawText("A", pos.x, pos.y, 60, RED);
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
