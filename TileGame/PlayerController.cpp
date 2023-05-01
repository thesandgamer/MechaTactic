#include "PlayerController.h"
#include "Game.h"
#include "CollisionManager.h"
#include "IInteraction.h"

PlayerController::PlayerController(): Controller()
{
}

PlayerController::~PlayerController()
{
}

void PlayerController::Start()
{
	name = "Player";

	//------Change the color of mecha to distinc if no models
	for (auto i = mechasList.begin(); i != mechasList.end(); i++)
	{
		(*i)->SetBaseColor({0,100,0,255});
	}

	Controller::Start();

	Texture2D buttonSprite = LoadTexture("Ressources/EndTurnButton.png");

	endTurnButton = new Button({ 10,10 }, buttonSprite, 128, 64);
	endTurnButton->textInButton = "End Turn";
	endTurnButton->AddFunctionToTrigger(std::bind(&PlayerController::FinishTurn,this));//Set la fonction de callback cr�er un fonction lambda

	//----Raycast to select
	ray = GetMouseRay(mousePos, *Game::instance().GetCamera());
	raycast.SetPosition(ray.position);
	raycast.checkingCollision = true;
	//raycast.trigger = true;
	


}

void PlayerController::Update()
{
	Controller::Update();
	if (!isTurn) return;
	PlayerDecideActions();
}

void PlayerController::Draw()
{
	Controller::Draw();

	raycast.Draw();

	if ((hitinfo.hit) && (abs(hitinfo.hitDistance) < raycast.GetLength()))
	{
		DrawSphereWires(hitinfo.hitPosition, 10, 20, 20, RED);
	}
	

}

void PlayerController::DrawUi()
{
	Controller::DrawUi();

	endTurnButton->Update();
	endTurnButton->Draw();
}



void PlayerController::PlayerDecideActions()
{
	mousePos = GetMousePosition();
	//mousePosInGrid = gridRef->PosInGrid(mousePos);

	CheckWhatBehindRay();

	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))	//Clique gauche
	{
		if (controledMecha == nullptr)	//Si on � pas de m�cha selectionn�
		{
			SelectMecha();
		}
		else	//Si on � un mecha de selection�
		{ 
			PrepareWhereMoveMecha();
		}
	}
	if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))	//Clique droit
	{
		if (controledMecha == nullptr)
		{
		
		}
		else if (controledMecha != nullptr)
		{
			DeSelectMecha();

		}

	}
}

void PlayerController::CheckWhatBehindRay()
{
	//Quand le tour du joueur est actif
	//Faire un rayon entre la camera et la souris (faire un truc � la unity Camera.screenPointToRay
	Vector3 direction{-1,-1,0};
	//ray = { Game::instance().GetCamera()->position,direction };
	ray = GetMouseRay(mousePos, *Game::instance().GetCamera());

	raycast.SetDirection(ray.direction);
	//R�cup�rer quel objet est sous mon rayon 

	

	if (CollisionManager::GetInstance()->DoRayCollision(&raycast, hitinfo))
	{
		//std::cout << "Hit: " << hitinfo.hitCollider->id << std::endl;
		//R�cup�rer l'acteur dans le collider touch�
		
		IInteraction* i = nullptr;
		if (hitinfo.hitCollider->Parent != nullptr)
		{
			i = dynamic_cast<IInteraction*>(hitinfo.hitCollider->Parent);
		}
		else
		{
			gridRef->ResetTilesColor();

		}

		if (i != nullptr)
		{
			i->OnHovered();
			ShowPath(i->GetPosInGrid());
		}
		else
		{
			gridRef->ResetTilesColor();

		}
		
	}
	else
	{
		gridRef->ResetTilesColor();

	}
}

void PlayerController::SelectMecha()
{
	
	if (hitinfo.IsCollideActor())
	{
		IInteraction* i = dynamic_cast<IInteraction*>(hitinfo.hitCollider->Parent);

		std::cout << "Mecha selected" << std::endl;
		//++ToDo: rajouter v�rfication
		controledMecha = dynamic_cast<MechaParent*>(hitinfo.hitCollider->Parent);

		if (i != nullptr)
		{
			i->OnClicked();
		}	
	}
}

void PlayerController::PrepareWhereMoveMecha()
{
	//++ToDo: si on � d�j� un m�cha, check si on clique sur une tuile vide et non pas un mecha,
	if (hitinfo.IsCollideActor())
	{
		Tile* i = dynamic_cast<Tile*>(hitinfo.hitCollider->Parent);
		if (i != nullptr)	//Si on � cliqu� sur une tuile
		{
			if (true)//Si sur une tuile vide v�rifie si y'a pas un m�chas dessus
			{
				Vector3 pos = i->GetPosInGrid();
				//R�cup�re la postion de la tuile et bouge le m�cha � cette tuile
				MoveMecha(pos);

				//controledMecha->MoveTo(pos);

			}

		}
	}
}

