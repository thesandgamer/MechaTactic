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
	endTurnButton->AddFunctionToTrigger(std::bind(&PlayerController::FinishTurn,this));//Set la fonction de callback créer un fonction lambda


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

	//DrawRay(ray, 100000, GREEN);
	//DrawSphere(ray.position, 5, RED);
	raycast.Draw();

	
	/*
	std::cout << "Have hit: " << hitinfo.hit << "\n";
	std::cout << "Hit location: " << hitinfo.position.x << " " << hitinfo.position.y << " " << hitinfo.position.z << "\n";
	std::cout << "Hit Distance: " << hitinfo.distance << "\n";
	*/
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
		if (controledMecha == nullptr)	//Si on à pas de mécha selectionné
		{
			//Select mecha
		}
		else	//Si on à un mecha de selectioné
		{ 
			//controller.MoveMecha();
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
	//Faire un rayon entre la camera et la souris (faire un truc à la unity Camera.screenPointToRay
	Vector3 direction{-1,-1,0};
	//ray = { Game::instance().GetCamera()->position,direction };
	ray = GetMouseRay(mousePos, *Game::instance().GetCamera());

	raycast.SetDirection(ray.direction);
	//Récupérer quel objet est sous mon rayon 

	

	if (CollisionManager::GetInstance()->DoRayCollision(&raycast, hitinfo))
	{
		std::cout << "Hit" << std::endl;

	}
	/*
	IInteraction* i = dynamic_cast<IInteraction*>(&hitinfo.hitCollider);

	if (i != nullptr)
	{
		i->OnHovered();
	}*/

	//GetCollisionRayModel()

	
 
	//Si le rayon collide une boite de collision, récupérer l'objet lié à la boite de collision
	//Appel la fonction hover de l'interface de l'objet touché par le rayon
}
