#include "MechaParent.h"
#include "Game.h"


//Constructeur à vide
MechaParent::MechaParent()
{
	position = { -1, -1 };
	gridRef = nullptr;
	informations = nullptr;
}

MechaParent::MechaParent(Vector2 positionP) : Actor(positionP)
{
	position = positionP;
	gridRef = nullptr;
	informations = nullptr;

	Init();
}

MechaParent::MechaParent(Vector2 positionP, Texture2D spriteP) : Actor(positionP)
{
	position = positionP;
	gridRef = nullptr;
	informations = nullptr;
	sprite = spriteP;

	Init();

}

MechaParent::MechaParent(Vector2 positionP, float widthP, float heightP) : Actor(positionP)
{
	position = positionP;
	width = widthP;
	height = heightP;
	gridRef = nullptr;
	informations = nullptr;

	Init();


}

MechaParent::~MechaParent()
{
}


void MechaParent::Init()
{
	informations = new InformationDisplay();
	informations->SetPos(&position);
	informations->infPasseur = this;

	gridRef = Game::instance().GetGrid();
	std::cout << sprite.width << std::endl;

}

void MechaParent::Draw()
{
	DrawVisual(position);
}


void MechaParent::Update()
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

	if (haveDoActions)
	{
		state = MechaState::NoActionsPossible;
	}
	else if (selected)
	{
		state = MechaState::SelectedGhost;
	}
	else
	{
		state = MechaState::NORMAL;
	}

}

void MechaParent::DrawVisual(Vector2 positionP)
{
	Color color = WHITE;

	switch (state)
	{
	case MechaState::NORMAL:
		color = WHITE;
		break;
	case MechaState::SelectedGhost:
		color = GRAY;

		break;
	case MechaState::NoActionsPossible:
		color = BLACK;
		break;
	case MechaState::Destroyed:
		break;
	default:
		break;
	}

	DrawRectangle(positionP.x * gridRef->CELL_WIDTH + width / 4 + gridRef->GetGridPos().x, positionP.y * gridRef->CELL_HEIGHT + height / 4 + gridRef->GetGridPos().y, width, height, color);




}


void MechaParent::MoveTo(Vector2 positionToGo)
{
	if (haveDoActions) return;

	//Si il n'y a pas de position à aller, finit
	//Appel le A star
	gridRef->Debug_CleanPathVisibility();
	poses = gridRef->aStar.GetPath({ position.x,position.y }, { positionToGo.x,positionToGo.y });
	canMove = true;
	currentTime = 0;
	positionIterator = 0;

}


//Ici on va set les informations affiché du mecha
string MechaParent::GetInformationOf()
{
	info += "Ma position: " + std::to_string(position.x) + " : " + std::to_string(position.y);
	informations->SetTitle(info);

	return info;
}

