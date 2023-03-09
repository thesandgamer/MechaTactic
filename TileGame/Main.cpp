#include "raylib.h"
#include <iostream>
#include <stdio.h>  
#include <math.h> 
#include <vector>
#include <string>
#include <map>

#include "Game.h"

//++ToDo: Faire en sorte de passer le jeu en 3d:
// Camera 3d: controllable(pour l'instant utiliser camear free)
// Selection de mecha par raycast à partir de la camera 
// Load de mesh pour les mechas, si le mesh est pas trouvé draw un debug cube
// En plus:
// Faire une map plus grande avec de la hauteur(map générée procéduralement)
// Faire en sorte que les mechas attatquent
// Faire une IA pour les mechas ennemis


using namespace std;

//Setup la taille de l'écran
int const SCREEN_WIDTH = 960;
int const SCREEN_HEIGHT = 540;

int main(int argc, char** argv[])
{

    //Créer un écran et on met les fps à 60
    string windowName = "Mecha Tactic";
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, windowName.c_str());

    //ToggleFullscreen();
    SetWindowPosition(0, 10);
    SetTargetFPS(60);

    Game::instance().SetupScreen(SCREEN_WIDTH, SCREEN_HEIGHT);

    Game::instance().Start();

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        Game::instance().Update();    
        Game::instance().Draw();
    }

    Game::instance().Clean();

    CloseWindow();

    return 0;


}

