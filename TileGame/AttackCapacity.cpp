#include "AttackCapacity.h"
#include "MechaParent.h"
#include "Controller.h"


AttackCapacity::AttackCapacity(MechaParent& mech): ActiveCapacity(mech)
{
	Texture2D sprite = LoadTexture("Ressources/AttackButton.png");
	button.SetSprite(sprite);
}

void AttackCapacity::ActivateCapacity(Actor* actorTarget)
{
	//Fait l'effet de la capacité
	std::cout << "Capacity is activated" << std::endl;
	DeselectCapacity();//The mech no longer have capacity selected

	linkToMech.GetOwner()->DeSelectMecha();	//The controller no longer have the mech selected

	linkToMech.SetState(MechaState::INCAPACITY);//The mech is now on capacity state

	if (actorTarget != nullptr)
	{
		if (dynamic_cast<MechaParent*>(actorTarget) != nullptr)
		{
			damagerDealer.MakeDamages(dynamic_cast<MechaParent*>(actorTarget)->GetLifeManager(), damageData);
		}
	}

	FinishCapacity();
}
