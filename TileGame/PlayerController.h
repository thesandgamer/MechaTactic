#pragma once
#include "Controller.h"

#include "RaycastCollision.h"
#include "CollisionManager.h"

class PlayerController: public Controller
{
public:
    

    PlayerController();
    ~PlayerController();

    void Start() override;
    void Update() override;
    void Draw() override;
    void DrawUi() override;

    void PlayerDecideActions();
    void CheckWhatBehindRay();
    void PrepareWhereMoveMecha();

    void SelectMecha();

private:

    void ComputeShowPath();

    Vector2 mousePos{0,0};
    Vector2 mousePosInGrid{ 0,0 };

    //Button* endTurnButton{nullptr}; //*Remplacer par smart pointer: le pointeur lui appartient
    std::unique_ptr<Button> endTurnButton;

    //----For raycast
    Ray ray{ {0,0,0},10000000 };
    RaycastCollision raycast{ {0,0,0},10000000 };
    RaycastHit hitinfo { false, {}, 0,{},{} };

    IInteraction* hitObject { nullptr };


    


};

