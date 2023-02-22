#include "Pawn.h"
#include "Game.h"


Pawn::Pawn()
{
	position = { -1, -1 };
	gridRef = nullptr;
	informations = nullptr;


}

Pawn::Pawn(Vector2 positionP): Actor(positionP)
{
	position = positionP;
	//gridRef = new Grid();
	gridRef = nullptr;
	informations = nullptr;
	

	Init();


}

Pawn::Pawn(Vector2 positionP, Texture2D spriteP) : Actor(positionP)
{
	position = positionP;
	gridRef = nullptr;
	//gridRef = new Grid();
	informations = nullptr;
	sprite = spriteP;

	Init();

}

Pawn::Pawn(Vector2 positionP, float widthP, float heightP) : Actor(positionP)
{
	position = positionP;
	width = widthP;
	height = heightP;
	gridRef = nullptr;
	//gridRef = new Grid();
	informations = nullptr;

	Init();


}

Pawn::~Pawn() 
{
}


std::vector<Vector2> poses;

void Pawn::Init()
{
	informations = new InformationDisplay();
	informations->SetPos(&position);
	informations->infPasseur = this;

	gridRef = Game::instance().GetGrid();
	std::cout << sprite.width << std::endl;

}

void Pawn::Draw()
{
	DrawVisual(position,selected);
}

int currentTime = 0; //Variable utilisé pour l'easing
int positionIterator = 0;
int duration = 40;

void Pawn::Update()
{
	
	if (canMove)
	{
		if (poses.empty()) return;
		Vector2 posToGo = poses[positionIterator];
		//Vector2AStar pos = { position.x,position.y };


		if (position.x == posToGo.x && position.y == posToGo.y)//Si on est arrivé à la position suivante
		{
			positionIterator++;//On augmente l'iterator
			currentTime = 0; //Et on reset le temps
		}

		position.x = EaseQuadInOut(currentTime, position.x, posToGo.x - position.x, duration);//On va au x suivant suivant un lerping
		position.y = EaseQuadInOut(currentTime, position.y, posToGo.y - position.y, duration);//On va au y suivant suivant un lerping

		currentTime++; //Augmente le temps

		if (positionIterator >= poses.size()) //Si on est arrivé à la fin des position où aller
		{

			canMove = false;
			haveDoActions = true;
			selected = false;
			return;
		}

	}
}

void Pawn::DrawVisual(Vector2 positionP,bool ghost)
{
	Color color = WHITE;
	if ((!haveDoActions) && (ghost))
	{
		color = GRAY;
	}

	if (sprite.width != NULL )
	{
		DrawTexture(sprite, positionP.x * gridRef->CELL_WIDTH + gridRef->GetGridPos().x,positionP.y * gridRef->CELL_HEIGHT + gridRef->GetGridPos().y, color);

	}
	else
	{
		DrawRectangle(positionP.x * gridRef->CELL_WIDTH + width / 4 + gridRef->GetGridPos().x, positionP.y * gridRef->CELL_HEIGHT + height / 4 + gridRef->GetGridPos().y, width, height, col);
	}
}


void Pawn::MoveTo(Vector2 positionToGo)
{
	if (haveDoActions) return;

	//Si il n'y a pas de position à aller, finit
	//Appel le A star
	gridRef->Debug_CleanPathVisibility();
	poses = gridRef->aStar.GetPath({position.x,position.y}, { positionToGo.x,positionToGo.y });
	canMove = true;
	currentTime = 0;
	positionIterator = 0;

}

string Pawn::GetInformationOf()
{
	info += "Ma position: " + std::to_string(position.x) + " : " + std::to_string(position.y);
	informations->SetTitle(info);

	return info;
}

