#include "Game.h"
#include "CollisionManager.h"

#include "ActiveCapacity.h"
#include "AttackCapacity.h"

#include "NetworkClient.h"
#include "NetworkServer.h"

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
    //++ToDo: faire en sorte d'avoir une fonction pour rajouter un obstacle qui va vérifier qu'on peut rajouter à cet endroit là

    obstacles.push_back(new Obstacle({ 5,0,5 }));
    obstacles.push_back(new Obstacle({ 3,0,3 }));
    obstacles.push_back(new Obstacle({ 4,0,7 }));
    obstacles.push_back(new Obstacle({ 7,0,6 }));
    obstacles.push_back(new Obstacle({ 2,0,8 }));
    obstacles.push_back(new Obstacle({ 1,0,2 }));
    obstacles.push_back(new Obstacle({ 6,0,2 }));

    for  (Obstacle * obstacle : obstacles)
    {
        obstacle->refToGrid = &grid;
        obstacle->Init();
    }


//=============Controllers Setup============
    PlayerController* p1 = new PlayerController();
    p1->name = "Tree Player";
    p1->AddMecha(   new TreeMech({ 1,0,4 }) );
    p1->AddMecha(   new TreeMech({ 8,0,8 }) );
    //Créer unique pointer pas stoqué car Add capacity à une R value(&&) (transfert de propritété)
    p1->GetMechaAt(0)->AddCapacity(std::make_unique<AttackCapacity>(*p1->GetMechaAt(0)) );
    p1->GetMechaAt(1)->AddCapacity(std::make_unique<AttackCapacity>(*p1->GetMechaAt(1)) );
    p1->GetMechaAt(1)->GetCurrentActiveCapacity();
    //{ player->GetMechaAt(0) }
    controllers.push_back(p1);   //Rajoute un player

    
    //--------Add Ennemy controller
    /*
    EnnemyController* ennemy = new EnnemyController();
    ennemy->AddMecha(  new MushMech({ 2,0,5 })  );
    ennemy->AddMecha(  new MushMech({ 5,0,2 })  );
    controllers.push_back(ennemy);
    */


    //-------Add another player
    PlayerController* p2 = new PlayerController();
    p2->name = "Mush Player";
    p2->AddMecha(new MushMech({ 2,0,5 }));
    p2->AddMecha(new MushMech({ 5,0,2 }));
    //Créer unique pointer pas stoqué car Add capacity à une R value(&&) (transfert de propritété)
    p2->GetMechaAt(0)->AddCapacity(std::make_unique<AttackCapacity>(*p2->GetMechaAt(0)));
    p2->GetMechaAt(1)->AddCapacity(std::make_unique<AttackCapacity>(*p2->GetMechaAt(1)));
    p2->GetMechaAt(1)->GetCurrentActiveCapacity();
    controllers.push_back(p2);   //Rajoute un player


    for (size_t i = 0; i < controllers.size(); i++)
    {
        controllers.at(i)->SetGrid(&grid);
        controllers[i]->Start();
      
    }
    /* Alt Version
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
    for  (Actor* obstacle : obstacles)
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
    for (auto i = vfxs.begin(); i != vfxs.end(); i++)
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

   //DrawCube({ 0,-32,0 }, 32, 32, 32, DARKPURPLE);    //Center of world
   //DrawCube({ 128,-32,128 }, 32, 32, 32, DARKPURPLE);    //Center of world

    for (Actor* obstacle : obstacles)
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

    for (auto i = vfxs.begin(); i != vfxs.end(); i++)
    {
        (*i)->Draw();
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

bool Game::SomethingAlreadyHere(Vector2 pos)
{


    //Check si y'a pas un mecha déjà là
    for (auto element : elementsInGame)
    {
        //element->GetPosition() == { pos.x, pos.y };
        if (element->GetPosInGrid().x == pos.x && element->GetPosInGrid().z == pos.y)
        {
            return true;
        }
    }

    if (grid.grid[pos.x][pos.y].traversible = false)
    {
        return true;
    }
    else
    {
        return false;

    }
}

void Game::CreateVFX(FX_Sprite* vfx)
{
    vfxs.push_back(vfx);
}

void Game::RemoveVFX(FX_Sprite* vfToRemove)
{
    vfxs.erase(std::find(vfxs.begin(), vfxs.end(), vfToRemove));
}


