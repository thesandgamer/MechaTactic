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

private:

    Vector2 mousePos{0,0};
    Vector2 mousePosInGrid{ 0,0 };

    Button* endTurnButton{nullptr};

    //----For raycast
    Ray ray{ {0,0,0},10000000 };
    RaycastCollision raycast{ {0,0,0},10000000 };
    RaycastHit hitinfo { false, {}, 0,{},{} };
    


};

