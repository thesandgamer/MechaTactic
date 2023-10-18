#include "PlayerController.h"
#include "Game.h"
#include "CollisionManager.h"
#include "IInteraction.h"

PlayerController::PlayerController(): Controller()
{
	name = "Player";

}

PlayerController::~PlayerController()
{
}

void PlayerController::Start()
{

	//------Change the color of mecha to distinc if no models
	for (auto i = mechasList.begin(); i != mechasList.end(); i++)
	{
		(*i)->SetBaseColor({204,102,0,255});	//Si on met plus de 255 comment ça marque erreur
	}

	Controller::Start();

	Texture2D buttonSprite = LoadTexture("Ressources/EndTurnButton.png");
	Vector2 buttonPos = { 10,10 };

	endTurnButton = std::make_unique<Button>( buttonPos, buttonSprite);

	endTurnButton->textInButton = "End Turn";
	endTurnButton->AddFunctionToTrigger(std::bind(&PlayerController::FinishTurn,this));//Set la fonction de callback créer un fonction lambda

	//----Raycast to select
	ray = GetMouseRay(mousePos, Game::instance().cam.GetCamera());
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

	if (isTurn)
	{
		endTurnButton->Update();
		endTurnButton->Draw();
	}
	
}



void PlayerController::PlayerDecideActions()
{
	mousePos = GetMousePosition();
	//mousePosInGrid = gridRef->PosInGrid(mousePos);
	CheckWhatBehindRay();


	if (!IsCurrentMechInAction())	//Si on à pas de mécha ou si celui quon à de séléctionné ne fait rien
	{

		//-------To show the path of the mecha selected
		if (controledMecha != nullptr)
		{
			if (controledMecha->GetState() != MechaState::MODE_CAPACITY)
			{
				if (cState == MechaMoveSelected)
					ComputeShowPath();
			}
			
		}


		
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))	//Clique gauche
		{
			if (hitObject != nullptr)
			{
				hitObject->OnClicked();
			}

			//Si j'ai un mécha séléctionné avec une capacité séléctionné, 
			//Si je clique sur quelque chose
				//Si ce queleque chose est à un endroit de la capacité

			if (controledMecha == nullptr)	//Si on à pas de mécha selectionné
			{
				SelectMecha();	//Check si on séléctionne un mécha
			}
			else	//Si on à un mecha de selectioné
			{
				if (controledMecha->GetState() == MechaState::MODE_MOVE)
				{
					PrepareWhereMoveMecha();
				}

				else if (controledMecha->GetState() == MechaState::MODE_CAPACITY)
				{
					if (hitObject != nullptr)
					{
						if (controledMecha->GetCurrentActiveCapacity()->InPossibleZone({ hitObject->GetPosInGrid().x,hitObject->GetPosInGrid().z }))
						{
							std::cout << "Case for capacity is good" << std::endl;
							//Put here code to activate active capacity 
							controledMecha->GetCurrentActiveCapacity()->ActivateCapacity(dynamic_cast<Actor*>(hitObject));
						}
					}
				}

			}
		}
		if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))	//Clique droit
		{
			if (controledMecha == nullptr)
			{

			}
			else if (controledMecha != nullptr)
			{
				if (controledMecha->GetState() == MechaState::MODE_CAPACITY)	//If current mecha have capacity selected
				{
					if(controledMecha->GetCurrentActiveCapacity() != nullptr)
						controledMecha->GetCurrentActiveCapacity()->DeselectCapacity();	
				}
				else
				{
					DeSelectMecha();

				}

			}

		}

	}

	
}

void PlayerController::CheckWhatBehindRay()
{
	//Quand le tour du joueur est actif
	//Faire un rayon entre la camera et la souris (faire un truc à la unity Camera.screenPointToRay
	Vector3 direction{-1,-1,0};
	//ray = { Game::instance().GetCamera()->position,direction };
	ray = GetMouseRay(mousePos, Game::instance().cam.GetCamera());

	raycast.SetDirection(ray.direction);
	//Récupérer quel objet est sous mon rayon 

	

	if (CollisionManager::GetInstance()->DoRayCollision(&raycast, hitinfo))	//Si le rayon touche
	{
		if (hitinfo.hitCollider->Parent != nullptr)	//Si la collision touché est attaché à un acteur
		{
			hitObject = dynamic_cast<IInteraction*>(hitinfo.hitCollider->Parent);	//Set l'objet touché
		}

		//Appel les fonctions de l'objet touché
		if (hitObject != nullptr)	//Si on à un objet sous la souris
		{
			hitObject->OnHovered();

			if (oldObject != nullptr)
			{
				if (hitObject != oldObject)	//Si on  pas sur le même
				{
					oldObject->OnEndHovered();

				}
			}
			oldObject = hitObject;
			if (cState == MechaSelected) cState = MechaMoveSelected;

		}
		else
		{
			if (cState == MechaMoveSelected)	gridRef->ResetTilesColor();  cState = MechaSelected;
			if (oldObject != nullptr)
			{
				oldObject->OnEndHovered();
				//oldObject = nullptr;
			}
		}
		
	}
	else
	{
		
		if (cState == MechaMoveSelected) gridRef->ResetTilesColor(); cState = MechaSelected;
		//hitObject = nullptr;
		if (oldObject != nullptr)
		{
			oldObject->OnEndHovered();
			oldObject = nullptr;
		}
	}


}

void PlayerController::SelectMecha()
{
	if (HitObjectIsMyMech())	//Si la souris est sur un acteur
	{
			std::cout << "Mecha selected" << std::endl;
			//++ToDo: rajouter vérfication
			controledMecha = dynamic_cast<MechaParent*>(hitinfo.hitCollider->Parent);
			controledMecha->Select();

			cState = MechaSelected;			
	}
}

void PlayerController::ComputeShowPath()
{
	if (controledMecha != nullptr)//Si on un mécha de séléctionné
	{
		if (hitObject != nullptr)	//Et si le on à touché un objet
		{
			if (controledMecha->GetState() != MechaState::INMOVEMENT && controledMecha->GetState() != MechaState::INCAPACITY
				&& controledMecha->GetState() != MechaState::DEACTIVATED)
			{
				if (!controledMecha->haveMove)
				{
					controledMecha->SetState(MechaState::MODE_MOVE); //Le mecha est donc en mode mouvement
					ShowPath(hitObject->GetPosInGrid());	//On affiche le chemin emprintable
				}
				
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

bool PlayerController::HitObjectIsMyMech()
{
	if (hitinfo.IsCollideActor())	//Si la souris est sur un acteur
	{
		if (dynamic_cast<MechaParent*>(hitinfo.hitCollider->Parent) != nullptr)	//Si c'est un mech de select
		{
			if (dynamic_cast<MechaParent*>(hitinfo.hitCollider->Parent)->GetOwner() == this)//Si il est à nous
			{
				return true;
			}
		}
	}
	return false;
}


/// <summary>
/// Make move the mecha 
/// </summary>
void PlayerController::PrepareWhereMoveMecha()
{
	//++ToDo: si on à déjà un mécha, check si on clique sur une tuile vide et non pas un mecha,
	if (hitinfo.IsCollideActor())
	{
		Tile* i = dynamic_cast<Tile*>(hitinfo.hitCollider->Parent);
		if (i != nullptr)	//Si on à cliqué sur une tuile
		{
			if (true)//Si sur une tuile vide vérifie si y'a pas un méchas dessus
			{
				//Récupère la postion de la tuile et bouge le mécha à cette tuile
				Vector3 pos = i->GetPosInGrid();

				MoveMecha(pos);

				//DeSelectMecha();


				
			}

		}
	}
}

