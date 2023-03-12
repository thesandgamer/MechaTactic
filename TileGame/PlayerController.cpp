#include "PlayerController.h"
#include "Game.h"

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
		(*i).SetBaseColor({0,100,0,255});

	}

	Controller::Start();

	Texture2D buttonSprite = LoadTexture("Ressources/EndTurnButton.png");

	endTurnButton = new Button({ 10,10 }, buttonSprite, 128, 64);
	endTurnButton->textInButton = "End Turn";
	endTurnButton->AddFunctionToTrigger(std::bind(&PlayerController::FinishTurn,this));//Set la fonction de callback créer un fonction lambda
	


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

	//ray.Draw();
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
	mousePosInGrid = gridRef->PosInGrid(mousePos);

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
	Vector3 direction;
	Ray ray{ Game::instance().GetCamera()->position,{0,0,0 } };
	DrawRay(ray, 10, GREEN);
	// 
	//Si le rayon collide une boite de collision, récupérer l'objet lié à la boite de collision
	//Appel la fonction hover de l'interface de l'objet touché par le rayon
}
