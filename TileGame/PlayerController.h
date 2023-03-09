#pragma once
#include "Controller.h"

#include "RaycastCollision.h"

//++ToDo: faire en sorte d'avoir un raycast, détécter ce qu'il y a sous le raycast

class PlayerController 
{
public:
    

    PlayerController();
    ~PlayerController();

    void Start();
    void Update();
    void Draw();
    void DrawUi();

    void PlayerDecideActions();
    void CheckWhatBehindRay();

private:
    Controller controller;

    Vector2 mousePos;
    Vector2 mousePosInGrid;

    Button* endTurnButton = nullptr;

    //----For raycast
    RaycastCollision ray{ {0,0,0},100000 };
    


};

