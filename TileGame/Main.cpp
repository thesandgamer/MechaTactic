#include "raylib.h"
#include <iostream>
#include <stdio.h>  
#include <math.h> 
#include <vector>
#include <string>
#include <map>

#include "Game.h"

//++ToDo: Faire en sorte de passer le jeu en 3d:
// Enlever le contrôle au joueur quand une unité s'active
// Camera 3d: controllable(pour l'instant utiliser camear free)
// Dessin du chemin que le mecha va emprinter: 
    // Indicateur du mecha selectionné
    // Indicateur de la case sur laquelle est la souris(mettre ça dans curseur)
    // Dessiner un chemin de cases en cases sur lequels va aller le mécha
// Ui qui montre notre team et quand on clique dessus ça les séléctionne et focus la cam dessus

// En plus:
// Faire en sorte que les mechas attatquent
// Faire une IA pour les mechas ennemis
// Améliorer le A* pour le rendre mieux
// Faire une map plus grande avec de la hauteur(map générée procéduralement), et avec un A* pas en grille


//++ToDo:
//  Créer un système pour permettre de mettre en lumière des cases:
//      Les cases sur lesquelles le mecha va se déplacer
//      Les cases d'attaque possible
//      ??NotNow?? les cases de déplacement possible
//

//
// Si on clique avec une capacité hors d'une bonne case déséléctionne la capacité
// Si on déséléctionne capacité repase en mode mouvement
// Si clique sur case pas acessible en mode déplacement déséléctionne le mécha
// Mecha reste séléctionné quand finit déplacement mais peut plus bouger
// 
//

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

