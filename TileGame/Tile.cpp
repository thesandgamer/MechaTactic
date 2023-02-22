#include "Tile.h"
#include "Grid.h"

Tile::Tile(): refToGrid{nullptr}, informations{nullptr}
{

}

Tile::Tile(int xP, int yP)
{
	pos.x = xP;
	pos.y = yP;
	traversible = true;
	refToGrid = nullptr;


}

Tile::Tile(int xP, int yP, float widthP, float heightP)
{
	pos.x = xP;
	pos.y = yP;
	width = widthP;
	height = heightP;
	traversible = true;
	refToGrid = nullptr;



}

void Tile::Init()
{
	informations = new InformationDisplay();
	informations->SetPos(&pos);
	informations->infPasseur = this;
}

void Tile::Draw()
{
	if (sprite.width != NULL)
	{
		DrawTexture(sprite, pos.x * refToGrid->CELL_WIDTH + refToGrid->GetGridPos().x, pos.y * refToGrid->CELL_HEIGHT + refToGrid->GetGridPos().y, WHITE);

	}
	else
	{
		DrawRectangle(pos.x * refToGrid->CELL_WIDTH + width / 4 + refToGrid->GetGridPos().x, pos.y * refToGrid->CELL_HEIGHT + height / 4 + refToGrid->GetGridPos().y, width, height, LIGHTGRAY);

	}
}

string Tile::GetInformationOf()
{
	string info = "    --Tile de Sol-- \nPas d'effet particulier";
	informations->SetTitle(info);

	return info;
}
