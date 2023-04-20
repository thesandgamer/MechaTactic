#include "Obstacle.h"

Obstacle::Obstacle()
{
}

Obstacle::Obstacle(Vector3 positionP) : Actor()
{
	/*
	informations = new InformationDisplay();
	informations->SetPos(&position);
	informations->infPasseur = this;*/
}

void Obstacle::Init()
{
}

void Obstacle::Draw()
{
	//DrawTexture(sprite, position.x * gridRef->CELL_WIDTH + gridRef->GetGridPos().x, position.y * gridRef->CELL_HEIGHT + gridRef->GetGridPos().y, WHITE);
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
