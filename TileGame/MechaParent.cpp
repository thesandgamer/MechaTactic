#include "MechaParent.h"
#include "Game.h"
#include "Controller.h"

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
	UnloadModel(model);
}


void MechaParent::Init()
{


	//-------Set collision
	//collision.modelToBoxing = &model;
	//collision = BoxCollision(&model);
	collision.SetParent(this);
	collision.id = "To test";


	//-----Setup le lien avec la grid
	gridRef = Game::instance().GetGrid();


	//Setup le model pour le dessiner
	if (model.meshCount == NULL)
	{
		drawColor = baseColor;
		model = LoadModelFromMesh(GenMeshCube(gridRef->CELL_WIDTH-10, gridRef->CELL_HEIGHT, gridRef->CELL_WIDTH-10));
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

	if (selected)
	{
		for (const auto& cap : capacities)
		{
			cap->Draw();
		}
	}

	
}

void MechaParent::DrawUI()
{
	if (canDrawLifeBar)
	{
		lifeBar.Draw();
		//std::cout << "DrawLifeBar" << std::endl;

	}


	if (!owner->isTurn)return;

	if (selected)
	{

		for (size_t i = 0; i < capacities.size(); i++)
		{
			capacities.at(i)->DrawUi();
			capacities.at(i)->DrawButton({ 10,120.0f + i*10 });
		}

		
	}


	

}


void MechaParent::Update()
{
	if (owner->isTurn)
	{

		//If the mech have to move make it move
		if (state == MechaState::INMOVEMENT)
		{
			MakeMovement();
		}
		//If the mech have to make capacity, make it
		if (state == MechaState::INCAPACITY)
		{
			//MakeCapacity();
		}

		//MakePassiveCapacity

		/*
		if (haveDoActions)
		{
			state = MechaState::DEACTIVATED;
		}
		else if (selected)
		{
			state = MechaState::SELECTED;
		}
		else
		{
			state = MechaState::IDLE;
		}*/

		if (selected)
		{
			for (const auto& cap : capacities)
			{
				cap->Update();
			}
		}
	}
	
	lifeBar.Update();


}

void MechaParent::StartTurn()
{
	haveDoActions = false;
	state = MechaState::IDLE;
}

void MechaParent::DrawVisual()
{

	switch (state)
	{
	case MechaState::IDLE:
		if (model.materialCount > 0)
		{
			drawColor = WHITE;
			break;
		}
		drawColor = baseColor;
		break;
	case MechaState::SELECTED:
		drawColor = GRAY;
		break;
	case MechaState::MODE_MOVE:
		drawColor = GRAY;
		break;
	case MechaState::MODE_CAPACITY:
		drawColor = GRAY;

		break;
	case MechaState::DEACTIVATED:
		drawColor = DARKGRAY;
		break;
	default:
		break;
	}

	DrawModel(model,transform.translation, transform.scale.x, drawColor);

}

/// <summary>
/// Tell the mech to move to a GridPosition
/// </summary>
/// <param name="positionToGo(InGrid)"></param>
void MechaParent::MoveTo(Vector3 positionToGo)
{
	if (haveDoActions) return;
	state = MechaState::INMOVEMENT;

	//gridRef->Debug_CleanPathVisibility();	//Inuitile pour l'instant
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
	//std::cout << "Hover" << std::endl;
	canDrawLifeBar = true;
	


}

void MechaParent::OnEndHovered()
{
	canDrawLifeBar = false;
}

void MechaParent::OnClicked()
{

}

void MechaParent::Select()
{
	if (haveDoActions) return;
	selected = true;
	state = MechaState::SELECTED;
}

void MechaParent::DeSelect()
{
	if (haveDoActions) return;

	selected = false;
	if (state != MechaState::INMOVEMENT && state != MechaState::INCAPACITY)
	{
		state = MechaState::IDLE;

	}
	
}

void MechaParent::AddCapacity(std::unique_ptr<Capacity>&& newCapacity)
{
	capacities.push_back(std::move(newCapacity));	//Std::move: pour transférer pour pas de copie
}

ActiveCapacity* MechaParent::GetCurrentActiveCapacity()
{
	return currentActiveCapacity;
}

void MechaParent::SetCurrentActiveCapacity(ActiveCapacity* capacity)
{
	currentActiveCapacity = capacity;
}

void MechaParent::EndActions()
{
	canMove = false;
	haveDoActions = true;

	DeSelect();
	state = MechaState::DEACTIVATED;
}

/// <summary>
/// Make actual movement for the mech
/// </summary>
void MechaParent::MakeMovement()
{
	if (canMove)
	{
		if (poses.empty()) return;
		Vector2 posToGo = poses[positionIterator];
		Vector3 posTo = gridRef->PosInGridToPosToWorld({ posToGo.x,0,posToGo.y });
		//Vector2AStar pos = { position.x,position.y };


		if (transform.translation.x == posTo.x && transform.translation.z == posTo.z)//Si on est arrivé à la position suivante
		{
			positionIterator++;//On augmente l'iterator
			currentTime = 0; //Et on reset le temps
			posInGrid = { posToGo.x,0,posToGo.y };//Set la position actuelle dans la grille
			gridRef->CalculateObstacles();

		}


		transform.translation.x = EaseQuadInOut(currentTime, transform.translation.x, posTo.x - transform.translation.x, duration);//On va au x suivant suivant un lerping
		transform.translation.z = EaseQuadInOut(currentTime, transform.translation.z, posTo.z - transform.translation.z, duration);//On va au y suivant suivant un lerping

		currentTime++; //Augmente le temps

		if (positionIterator >= poses.size()) //Si on est arrivé à la fin des position où aller
		{
			EndActions();

			return;
		}

	}
}

