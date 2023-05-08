#pragma once
#include "Capacity.h"

#include <iostream>
#include <vector>

class MechaParent;


class ActiveCapacity :
    public Capacity
{
public:
    ActiveCapacity(MechaParent& mech);

    void Init() override;

    void DrawPossibleZone() override;

private:

    std::vector<std::vector<int>> possibleZone{};

    MechaParent& linkToMech ;

};

//++ToDo:
//  Capacité active Parente
//  Image / bouton qui lui est lié
//  Affichage de où peut s'effectuer la capacité
//  Effectuage de l'effet de la capcité
//

