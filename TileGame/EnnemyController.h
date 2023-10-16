#pragma once
#include "Controller.h"
class EnnemyController :
    public Controller
{
public:
    EnnemyController();
    ~EnnemyController();

    void Start() override;
    void Update() override;


    void StartTurn() override;

private:

    void AIActions();

    int it{ 0 };
};

