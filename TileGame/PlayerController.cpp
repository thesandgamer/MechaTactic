#include "PlayerController.h"

PlayerController::PlayerController()
{
}

PlayerController::~PlayerController()
{
}

void PlayerController::Start()
{
	controller.name = "Player";

	Texture2D buttonSprite = LoadTexture("Ressources/EndTurnButton.png");

	endTurnButton = new Button({ 10,10 }, buttonSprite, 128, 64);
	endTurnButton->textInButton = "End Turn";
	endTurnButton->setCallback(std::bind(&Controller::FinishTurn,&controller));//Set la fonction de callback créer un fonction lambda
	
}

void PlayerController::Update()
{
	if (!controller.isTurn) return;
	PlayerDecideActions();
}

void PlayerController::Draw()
{
	ray.Draw();
}

void PlayerController::DrawUi()
{
	endTurnButton->Update();
	endTurnButton->Draw();
}



void PlayerController::PlayerDecideActions()
{
	mousePos = GetMousePosition();
	mousePosInGrid = controller.gridRef->PosInGrid(mousePos);

	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))	//Clique gauche
	{
		if (controller.controledMecha == nullptr)	//Si on à pas de mécha selectionné
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
		if (controller.controledMecha == nullptr)
		{
		
		}
		else if (controller.controledMecha != nullptr)
		{
			controller.DeSelectMecha();

		}

	}
}

void PlayerController::CheckWhatBehindRay()
{
}
