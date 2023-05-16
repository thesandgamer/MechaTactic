#pragma once
#include "Capacity.h"

#include <iostream>
#include <vector>

#include "Button.h"

class MechaParent;


class ActiveCapacity :
    public Capacity
{
public:
    ActiveCapacity(MechaParent& mech);

    void Init() override;
    void Draw() override;
    void Update() override;
    void DrawUi() override;

    void DrawPossibleZone() override;

    void ButtonClicked();
    void SelectCapacity();
    void DeselectCapacity();

    bool InPossibleZone(Vector2 pos);

    void SetPossibleZoneInGrid();

private:
    Button button { {10,120},40,40 };


    std::vector<std::vector<int>> possibleZone{};

    std::vector<Vector2> possibleZoneInGrid{};

    MechaParent& linkToMech ;

    bool isActive {false};

};

//++ToDo:
//  Capacité active Parente
//  Image / bouton qui lui est lié
//  Affichage de où peut s'effectuer la capacité
//  Effectuage de l'effet de la capcité
//

