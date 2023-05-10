#include "Game.h"
#include "CollisionManager.h"

#include "ActiveCapacity.h"

void Game::SetupScreen(int screenwidth, int screenHeight)
{
    SCREEN_WIDTH = screenwidth;
    SCREEN_HEIGHT = screenHeight;
}

void Game::Start()
{
//===========Setup la Grille==============
    const static int GRID_WIDTH = 9;
    const static int GRID_LENGTH = 9;
    const static int GRID_HEIGHT = 1;

    const static int CELL_WIDTH = 32;
    const static int CELL_LENGTH = 32;
    const static int CELL_HEIGHT = 32;
    //Vector2 gridPos = { SCREEN_WIDTH / 2 - (GRID_WIDTH * CELL_WIDTH) / 2 ,SCREEN_HEIGHT / 2 - (GRID_HEIGHT * CELL_HEIGHT) / 2 };
    Vector3 gridPos = { - (GRID_WIDTH * (CELL_WIDTH) /2 - CELL_WIDTH/2)  ,0, -(GRID_LENGTH * (CELL_LENGTH) /2 - CELL_LENGTH/2) }; //Center grid in world


    grid = Grid(gridPos, {GRID_WIDTH,GRID_HEIGHT,GRID_LENGTH}); //On génère la grille
    grid.Start();


//=========Setup la camera==========
    cam.Init();

//=========Setup les obstacles==========
    obstacles.push_back(new Obstacle({ 2,0,2 }));
    obstacles.push_back(new Obstacle({ 8,0,3 }));
    obstacles.push_back(new Obstacle({ 8,0,5 }));
    obstacles.push_back(new Obstacle({ 3,0,8 }));

    for each (Obstacle * obstacle in obstacles)
    {
        obstacle->refToGrid = &grid;
        obstacle->Init();
    }


//=============Controllers Setup============
    PlayerController* player = new PlayerController();
    player->AddMecha({ 4,0,4 });
   // player->AddMecha({ 4,0,4 });
    player->GetMechaAt(0)->AddCapacity(new ActiveCapacity(*player->GetMechaAt(0)) );
    //{ player->GetMechaAt(0) }
    controllers.push_back(player);   //Rajoute un player

    //++ToDo: fait en sorte que ça marche avec plusieurs player controller

    for (size_t i = 0; i < controllers.size(); i++)
    {
        controllers.at(i)->SetGrid(&grid);
        controllers[i]->Start();
      
    }
    /*
    for (auto i = controllers.begin(); i != controllers.end(); i++)
    {
        (*i)->SetGrid(&grid);
        (*i)->Start();
        
    }*/

//=============Setup Cursor===========
    cursor.Start();

//============Setup elements in game==============

    // Rajoute tout les méchas de tous les controllers dans les éléments in game(sert d'obstacles)
    for (auto i = controllers.begin(); i != controllers.end(); i++)
    {
        for (int j = 0; j < (*i)->GetNumberOfMechas(); j++)
        {
           elementsInGame.push_back((*i)->GetMechaAt(j));  //Rajoute tous les méchas
        }

    }

    //Rajoute obstacles
    for each (Actor* obstacle in obstacles)
    {
        elementsInGame.push_back(obstacle);
    }


//===========Setup les info==========
    /*
    infoUi = new InformationDisplayUi();
    infoUi->SetPosition({ (float)SCREEN_WIDTH - SCREEN_WIDTH / 3,0 });

    //Get les info des pawns du player
    for (int i = 0; i < player.GetPawns()->size(); i++)
    {
        informations.push_back(player.GetPawns()->at(i).GetInformations());
    }
    //Get les info des pawns de l'ennemi
    for (int i = 0; i < player.GetPawns()->size(); i++)
    {
        informations.push_back(ennemy.GetPawns()->at(i).GetInformations());
    }
    //Get les informations des obstacles
    for each (Obstacle * obstacle in obstacles)
    {
        informations.push_back(obstacle->GetInformations());
    }
    

                    //------Forcément de Dernier----------
    //On va parcourir toutes les tiles de la grille et récupérer les informaion pour les mettre dans informations
    for (int i = 0; i < grid.grid.size(); i++)
    {
        for (int j = 0; j < grid.grid[i].size(); j++)
        {
            informations.push_back(grid.grid[i][j].GetInformations());
        }
    }
    */


//=========Setup Turn Manager===========
    for (auto i = controllers.begin(); i != controllers.end(); i++)
    {
        turnManager.AddSomethingMakeTurn(*i);
    }
    turnManager.Start();



}

void Game::Update()
{
    turnManager.Update();
    grid.Update();

    CollisionManager::GetInstance()->Update();

    for (auto i = controllers.begin(); i != controllers.end(); i++)
    {
        (*i)->Update();
    }

    cursor.Updtate();
    cam.Update();

//=======Updtate infos=========
    /* Ca n'a pas à être là, avoir cette feature dans les player controller
    for (InformationDisplay* inf : informations)
    {
        if (inf->GetPos().x == player.GetMousePosInGrid().x && inf->GetPos().y == player.GetMousePosInGrid().y)
        {
            //Quand on est sur l'info display, faire en sorte d'appeler la fonction pour setup le texte
            inf->infPasseur->GetInformationOf();
            infoUi->infoLinkedTo = inf;
            break;
        }
        else
        {
            infoUi->infoLinkedTo = nullptr;
        }
    }*/
}

void Game::Draw()
{
    BeginDrawing();
    ClearBackground(BLACK);
    BeginMode3D(cam.GetCamera());

   // DrawGrid(32, 32);
    grid.Draw();

   // DrawCube({ 0,-32,0 }, 32, 32, 32, DARKPURPLE);    //Center of world

    for each (Actor* obstacle in obstacles)
    {
        obstacle->Draw();
    }

    for (auto i = controllers.begin(); i != controllers.end(); i++)
    {
        (*i)->Draw();
    }

    cam.Draw();

    CollisionManager::GetInstance()->Draw();

    EndMode3D();

    DrawUi();
    
    EndDrawing();
}

void Game::DrawUi()
{
    for (auto i = controllers.begin(); i != controllers.end(); i++)
    {
        (*i)->DrawUi();
    }
    cursor.Draw();

//=======Draw les infos========
    //infoUi->Draw();

//=======
    turnManager.DrawUi();
}

void Game::Clean()
{

}
