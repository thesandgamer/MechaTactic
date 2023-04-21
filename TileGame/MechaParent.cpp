#include "MechaParent.h"
#include "Game.h"


//Constructeur à vide
MechaParent::MechaParent()
{
	posInGrid = { 0,0,0 };
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
	collision.modelToBoxing = &model;
	//collision = BoxCollision(&model);
	collision.SetParent(this);
	collision.id = "To test";


	//-----Setup le lien avec la grid
	gridRef = Game::instance().GetGrid();


	//Setup le model pour le dessiner
	if (model.meshCount == NULL)
	{
		drawColor = baseColor;
		model = LoadModelFromMesh(GenMeshCube(gridRef->CELL_WIDTH, gridRef->CELL_HEIGHT, gridRef->CELL_WIDTH));
	}

	//----Init les collisions
	collision.Init();



	//-----Setup des informations
	informations = new InformationDisplay();
	informations->SetPos(&posInGrid);
	informations->infPasseur = this;


	//----Set sa postion in world depending of is position in grid
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
		Vector3 posTo = gridRef->PosInGridToPosToWorld({posToGo.x,0,posToGo.y});
		//Vector2AStar pos = { position.x,position.y };


		if (transform.translation.x == posTo.x && transform.translation.z == posTo.z)//Si on est arrivé à la position suivante
		{
			positionIterator++;//On augmente l'iterator
			currentTime = 0; //Et on reset le temps
			posInGrid = { posToGo.x,0,posToGo.y };//Set la position actuelle dans la grille

		}
		

		transform.translation.x = EaseQuadInOut(currentTime, transform.translation.x, posTo.x - transform.translation.x, duration);//On va au x suivant suivant un lerping
		transform.translation.z = EaseQuadInOut(currentTime, transform.translation.z, posTo.z - transform.translation.z, duration);//On va au y suivant suivant un lerping

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
	
	drawColor = WHITE;

	switch (state)
	{
	case MechaState::NORMAL:
		drawColor = WHITE;
		break;
	case MechaState::SelectedGhost:
		drawColor = GRAY;
		break;
	case MechaState::Selected:
		drawColor = GRAY;
		break;
	case MechaState::NoActionsPossible:
		drawColor = BLACK;
		break;
	case MechaState::Destroyed:
		break;
	default:
		break;
	}

	DrawModel(model,transform.translation, transform.scale.x, drawColor);

}


void MechaParent::MoveTo(Vector3 positionToGo)
{
	if (haveDoActions) return;
	//Si il n'y a pas de position à aller, finit
	//Appel le A star
	gridRef->Debug_CleanPathVisibility();
	poses = gridRef->aStar.GetPath({ posInGrid.x,posInGrid.z }, { positionToGo.x,positionToGo.z });
	canMove = true;
	currentTime = 0;
	positionIterator = 0;

}


//Ici on va set les informations affiché du mecha
string MechaParent::GetInformationOf()
{
	info += "Ma position: " + std::to_string(posInGrid.x) + " : " + std::to_string(posInGrid.z);
	informations->SetTitle(info);

	return info;
}

void MechaParent::OnHovered()
{
}

void MechaParent::OnClicked()
{
	state = MechaState::Selected;
	selected = true;
}

