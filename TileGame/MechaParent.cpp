#include "MechaParent.h"
#include "Game.h"


//Constructeur à vide
MechaParent::MechaParent()
{
	position = { -1, -1 };
	gridRef = nullptr;
	informations = nullptr;
}

MechaParent::MechaParent(Vector3 positionP)
{
	posInGrid = positionP;
	//Init();
}

MechaParent::MechaParent(Vector3 positionP, Model modelP): model{modelP}
{
	posInGrid = positionP;
	//Init();
}


MechaParent::~MechaParent()
{

}


void MechaParent::Init()
{
	//-------Set collision
	collision = BoxCollision(&model);
	collision.SetParent(&transform);
	collision.id = "To test";


	//-----Setup le lien avec la grid
	gridRef = Game::instance().GetGrid();


	//Setup le model pour le dessiner
	if (model.meshCount == NULL)
	{
		drawColor = baseColor;
		model = LoadModelFromMesh(GenMeshCube(gridRef->CELL_WIDTH, gridRef->CELL_HEIGHT, gridRef->CELL_WIDTH));
	}

	collision.Init();



	//-----Setup des informations
	informations = new InformationDisplay();
	informations->SetPos(&position);
	informations->infPasseur = this;


	transform.translation = gridRef->PosInGridToPosToWorld(posInGrid);

	

}

void MechaParent::Draw()
{
	DrawVisual();
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

void MechaParent::DrawVisual()
{
	/*
	drawColor = WHITE;

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
	}*/

	DrawModel(model,transform.translation, transform.scale.x, drawColor);

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

