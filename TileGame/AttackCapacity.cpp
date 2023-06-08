#include "AttackCapacity.h"
#include "MechaParent.h"
#include "Controller.h"

#include "Game.h"
#include "Utility.h"

AttackCapacity::AttackCapacity(MechaParent& mech): ActiveCapacity(mech)
{
	Init();
}

void AttackCapacity::Init()
{
	Texture2D sprite = LoadTexture("Ressources/AttackButton.png");
	button.SetSprite(sprite);
	button.AddFunctionToTrigger(std::bind(&ActiveCapacity::ButtonClicked, this));
	button.AddHoverFunction(std::bind(&ActiveCapacity::DrawPossibleZone, this));
	button.lever = true;


	possibleZone = {
	{0,0,1,1,1},
	{0,0,1,0,0},
	{1,1,5,1,0},
	{0,0,0,1,0},
	{0,0,0,1,0},

	};
}

void AttackCapacity::ActivateCapacity(Actor* actorTarget)
{
	//Fait l'effet de la capacité
	ActiveCapacity::ActivateCapacity(actorTarget);
	/*
	std::cout << "Capacity is activated" << std::endl;
	DeselectCapacity();//The mech no longer have capacity selected

	linkToMech.GetOwner()->DeSelectMecha();	//The controller no longer have the mech selected

	linkToMech.SetState(MechaState::INCAPACITY);//The mech is now on capacity state
	*/
	if (actorTarget != nullptr)
	{
		Game::instance().CreateVFX(new FX_Sprite(Utility::GetInstance()->fxExplosion, 6, 10, actorTarget->GetPosition()));

		if (dynamic_cast<MechaParent*>(actorTarget) != nullptr)
		{
			damagerDealer.MakeDamages(dynamic_cast<MechaParent*>(actorTarget)->GetLifeManager(), damageData);
		}
	}

	FinishCapacity();
}
