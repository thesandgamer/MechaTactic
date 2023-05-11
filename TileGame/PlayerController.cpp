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
		(*i)->SetBaseColor({200,150,0,255});	//Si on met plus de 255 comment �a marque erreur
	}

	Controller::Start();

	Texture2D buttonSprite = LoadTexture("Ressources/EndTurnButton.png");
	Vector2 buttonPos = { 10,10 };

	endTurnButton = std::make_unique<Button>( buttonPos, buttonSprite, 128, 64 );

	endTurnButton->textInButton = "End Turn";
	endTurnButton->AddFunctionToTrigger(std::bind(&PlayerController::FinishTurn,this));//Set la fonction de callback cr�er un fonction lambda

	//----Raycast to select
	ray = GetMouseRay(mousePos, Game::instance().cam.GetCamera());
	raycast.SetPosition(ray.position);
	raycast.checkingCollision = true;
	//raycast.trigger = true;
	


}

void PlayerController::Update()
{
	if (!isTurn) return;

	Controller::Update();
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

	if (!IsCurrentMechInAction())
	{
		
		if (cState == MechaMoveSelected)
			ComputeShowPath();

		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))	//Clique gauche
		{
			if (hitObject != nullptr)
			{
				hitObject->OnClicked();
			}

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

	
}

void PlayerController::CheckWhatBehindRay()
{
	//Quand le tour du joueur est actif
	//Faire un rayon entre la camera et la souris (faire un truc � la unity Camera.screenPointToRay
	Vector3 direction{-1,-1,0};
	//ray = { Game::instance().GetCamera()->position,direction };
	ray = GetMouseRay(mousePos, Game::instance().cam.GetCamera());

	raycast.SetDirection(ray.direction);
	//R�cup�rer quel objet est sous mon rayon 

	

	if (CollisionManager::GetInstance()->DoRayCollision(&raycast, hitinfo))
	{

		if (hitinfo.hitCollider->Parent != nullptr)	//Si la collision touch� est attach� � un acteur
		{
			hitObject = dynamic_cast<IInteraction*>(hitinfo.hitCollider->Parent);	//Set l'objet touch�
		}

		//Appel les fonctions de l'objet touch�
		if (hitObject != nullptr)
		{
			hitObject->OnHovered();
			if (cState == MechaSelected) cState = MechaMoveSelected;

		}
		else
		{
			if (cState == MechaMoveSelected)	gridRef->ResetTilesColor();  cState = MechaSelected;
		}
		
	}
	else
	{
		if (cState == MechaMoveSelected) gridRef->ResetTilesColor(); cState = MechaSelected;
	}


}

void PlayerController::SelectMecha()
{
	if (hitinfo.IsCollideActor())
	{
		if (dynamic_cast<MechaParent*>(hitinfo.hitCollider->Parent) != nullptr)
		{
			std::cout << "Mecha selected" << std::endl;
			//++ToDo: rajouter v�rfication
			controledMecha = dynamic_cast<MechaParent*>(hitinfo.hitCollider->Parent);
			controledMecha->Select();

			cState = MechaSelected;

		}		
	}
}

void PlayerController::ComputeShowPath()
{
	if (controledMecha != nullptr)//Si on un m�cha de s�l�ctionn�
	{
		if (hitObject != nullptr)	//Et si le on � touch� un objet
		{
			if (controledMecha->GetState() != MechaState::INMOVEMENT && controledMecha->GetState() != MechaState::INCAPACITY)
			{
				controledMecha->SetState(MechaState::MODE_MOVE); //Le mecha est donc en mode mouvement
				ShowPath(hitObject->GetPosInGrid());	//On affiche le chemin emprintable
			}
			
		}
		else
		{
			gridRef->ResetTilesColor();

		}
		
	}
	else
	{
		//gridRef->ResetTilesColor();
	}
}


/// <summary>
/// Make move the mecha 
/// </summary>
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
				//R�cup�re la postion de la tuile et bouge le m�cha � cette tuile
				Vector3 pos = i->GetPosInGrid();

				MoveMecha(pos);

				DeSelectMecha();


				
			}

		}
	}
}

