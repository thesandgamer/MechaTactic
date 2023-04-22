#include "Obstacle.h"

Obstacle::Obstacle()
{
}

Obstacle::Obstacle(Vector3 positionP) : Actor()
{
	posInGrid = positionP;

	/*
	informations = new InformationDisplay();
	informations->SetPos(&position);
	informations->infPasseur = this;*/
}

void Obstacle::Init()
{
	//-------Set collision
	collision = BoxCollision(&model);
	collision.SetParent(this);
	collision.id = "ObstacleCollision";

	collision.Init();

	if (model.meshCount == NULL)//Si on à pas de mesh de loadé, load un cube
	{
		drawColor = DARKGRAY;
		model = LoadModelFromMesh(GenMeshCube(Grid::CELL_WIDTH, Grid::CELL_HEIGHT, Grid::CELL_LENGTH));
	}

	transform.translation = refToGrid->PosInGridToPosToWorld(posInGrid);
}

void Obstacle::Draw()
{
	//DrawTexture(sprite, position.x * gridRef->CELL_WIDTH + gridRef->GetGridPos().x, position.y * gridRef->CELL_HEIGHT + gridRef->GetGridPos().y, WHITE);
	DrawModel(model, transform.translation, transform.scale.x, drawColor);
}

void Obstacle::Update()
{
}

string Obstacle::GetInformationOf()
{
	string info = "    --Faille-- \nBloque les deplacements";
	informations->SetTitle(info);

	return info;
}
