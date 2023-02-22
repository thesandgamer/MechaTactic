#include "Obstacle.h"

Obstacle::Obstacle()
{
}

Obstacle::Obstacle(Vector2 positionP, Texture2D spriteP) :Actor(positionP,spriteP)
{
	informations = new InformationDisplay();
	informations->SetPos(&position);
	informations->infPasseur = this;
}

void Obstacle::Draw()
{
	DrawTexture(sprite, position.x * gridRef->CELL_WIDTH + gridRef->GetGridPos().x, position.y * gridRef->CELL_HEIGHT + gridRef->GetGridPos().y, WHITE);
}

string Obstacle::GetInformationOf()
{
	string info = "    --Faille-- \nBloque les deplacements";
	informations->SetTitle(info);

	return info;
}
