#include "Cursor.h"
#include "Game.h"

Cursor::Cursor()
{
}

Cursor::Cursor(Vector2 positionP): position{positionP}
{
	state = CusorState::NOONE;
}

Cursor::~Cursor()
{
	state = CusorState::NOONE;
}

void Cursor::Start()
{
	gridRef = Game::instance().GetGrid();
}

void Cursor::Updtate()
{
	/*
	mousePos = GetMousePosition();
	mousePosInGrid = gridRef->PosInGrid(mousePos);
	position = mousePos;
	*/
}

void Cursor::Draw()
{
	/*	OLD revoir le fonctionnement du curseur
	Color col = GREEN;
	float x = mousePosInGrid.x * gridRef->CELL_WIDTH ;
	float y = mousePosInGrid.y * gridRef->CELL_HEIGHT ;

	
	if (mousePosInGrid.x >= 0 && mousePosInGrid.x < gridRef->GRID_WITH && mousePosInGrid.y >= 0 && mousePosInGrid.x < gridRef->GRID_HEIGHT)//Si on est dans la grille
	{
		//Cas Hover
		
		vector<Pawn>* actors = Game::instance().GetPlayer()->GetPawns();//A modifier
		for (int i = 0; i < actors->size(); i++)
		{	
			if (actors->at(i).position.x == mousePosInGrid.x && actors->at(i).position.y == mousePosInGrid.y)
			{
				state = CusorState::PAWN_HOVERED;
				break;
			}
			else
			{
				state = CusorState::SELECT;
			}
		}

		//Cas pawn séléctionné
		if (Game::instance().GetPlayer()->GetControledPawn() != nullptr) //Si on à un pawn de select
		{

			if (!Game::instance().GetPlayer()->GetControledPawn()->haveDoActions)//Si la pawn peut encore se déplacer
			{
				for each (Actor* act in Game::instance().GetElementsInGame())
				{
					if (act->position.x == mousePosInGrid.x && act->position.y == mousePosInGrid.y)
					{
						state = CusorState::PAWN_POS_BLOCKED;
						break;
					}
					else
					{
						state = CusorState::PAWN_MOVEMENT;

					}
				}
			}
			else
			{
				state = CusorState::PAWN_CAN_NOT_MOVE;
			}
		}
		
		
	}
	else
	{
		state = CusorState::NOONE;
	}



	switch (state)
	{
	case CusorState::NOONE:
		break;
	case CusorState::SELECT:
		DrawRectangleLines(x + gridRef->GetGridPos().x, y + gridRef->GetGridPos().y, gridRef->CELL_WIDTH, gridRef->CELL_HEIGHT, YELLOW);
		break;
	case CusorState::PAWN_HOVERED:
		DrawRectangleLines(x + gridRef->GetGridPos().x, y + gridRef->GetGridPos().y, gridRef->CELL_WIDTH, gridRef->CELL_HEIGHT, PURPLE);
		//Show les movements
		break;

	case CusorState::PAWN_MOVEMENT:
		Game::instance().GetPlayer()->GetControledPawn()->DrawVisual(mousePosInGrid,false);
		//Draw Path
		//Surlignage mecha
		break;

	case CusorState::PAWN_POS_BLOCKED:
		DrawRectangleLines(x + gridRef->GetGridPos().x, y + gridRef->GetGridPos().y, gridRef->CELL_WIDTH, gridRef->CELL_HEIGHT, RED);
		break;

	case CusorState::PAWN_CAN_NOT_MOVE:
		DrawRectangleLines(x + gridRef->GetGridPos().x, y + gridRef->GetGridPos().y, gridRef->CELL_WIDTH, gridRef->CELL_HEIGHT, YELLOW);
		//Surlignage Mecha

		break;

	default:
		break;
	}


	//Draw le curseur
	//DrawRectangle(position.x, position.y, gridRef->CELL_WIDTH /2 , gridRef->CELL_HEIGHT /2, col);
	*/

}
