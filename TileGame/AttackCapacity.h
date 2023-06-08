#pragma once
#include "ActiveCapacity.h"

#include "DamageDealer.h"


class AttackCapacity :
    public ActiveCapacity
{
public:
    AttackCapacity(MechaParent& mech);

    void Init() override;
    void ActivateCapacity(Actor* actorTarget) override;


private:
    DamageDealer damagerDealer{};
    DamageData damageData{1,0};

};

