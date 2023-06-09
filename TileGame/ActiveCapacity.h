#pragma once
#include "Capacity.h"

#include <iostream>
#include <vector>

#include "Button.h"
#include "Actor.h"



class MechaParent;

/// <summary>
/// Not used for now
/// </summary>
enum CanBeActivateOnWhat {

};

//++ToDo: make draw possible zone when button is hivered;

class ActiveCapacity :
    public Capacity
{
public:
    ActiveCapacity(MechaParent& mech);

    void Init() override;
    void Draw() override;
    void Update() override;
    void DrawUi() override;
    void DrawButton(Vector2 pos) override;
    

    void DrawPossibleZone() override;

    void ButtonClicked();
    void SelectCapacity();
    void DeselectCapacity();

    bool InPossibleZone(Vector2 pos);

    void SetPossibleZoneInGrid();
    
    virtual void ActivateCapacity(Actor* actorTarget);

    void FinishCapacity();

    void Reset();

protected:
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

