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
//  Capacit� active Parente
//  Image / bouton qui lui est li�
//  Affichage de o� peut s'effectuer la capacit�
//  Effectuage de l'effet de la capcit�
//

