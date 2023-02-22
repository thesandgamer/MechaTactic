#include "Actor.h"
#include "Game.h"

Actor::Actor()
{
}

Actor::Actor(Vector2 positionP): position{positionP}, gridRef{nullptr}, sprite{}
{
}

Actor::Actor(Vector2 positionP, Texture2D spriteP): position{ positionP }, sprite{spriteP}, gridRef{ nullptr }
{
}

void Actor::Init()
{
	gridRef = Game::instance().GetGrid();
}

void Actor::Draw()
{
	if (sprite.width != NULL)
	{
		DrawTexture(sprite, position.x * gridRef->CELL_WIDTH + gridRef->GetGridPos().x, position.y * gridRef->CELL_HEIGHT + gridRef->GetGridPos().y, WHITE);

	}
	else
	{
		DrawRectangle(position.x * gridRef->CELL_WIDTH  + gridRef->GetGridPos().x, position.y * gridRef->CELL_HEIGHT + gridRef->GetGridPos().y, gridRef->CELL_WIDTH, gridRef->CELL_HEIGHT, BROWN);

	}

}
