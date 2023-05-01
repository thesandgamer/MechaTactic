#include "raylib.h"
#include <iostream>
#include <stdio.h>  
#include <math.h> 
#include <vector>
#include <string>
#include <map>

#include "Game.h"

//++ToDo: Faire en sorte de passer le jeu en 3d:
// Enlever le contr�le au joueur quand une unit� s'active
// Camera 3d: controllable(pour l'instant utiliser camear free)
// Dessin du chemin que le mecha va emprinter: 
    // Indicateur du mecha selectionn�
    // Indicateur de la case sur laquelle est la souris(mettre �a dans curseur)
    // Dessiner un chemin de cases en cases sur lequels va aller le m�cha
// Ui qui montre notre team et quand on clique dessus �a les s�l�ctionne et focus la cam dessus

// En plus:
// Faire en sorte que les mechas attatquent
// Faire une IA pour les mechas ennemis
// Am�liorer le A* pour le rendre mieux
// Faire une map plus grande avec de la hauteur(map g�n�r�e proc�duralement), et avec un A* pas en grille


using namespace std;

//Setup la taille de l'�cran
int const SCREEN_WIDTH = 960;
int const SCREEN_HEIGHT = 540;

int main(int argc, char** argv[])
{

    //Cr�er un �cran et on met les fps � 60
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

