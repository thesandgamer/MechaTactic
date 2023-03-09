#include "Game.h"

void Game::SetupScreen(int screenwidth, int screenHeight)
{
    SCREEN_WIDTH = screenwidth;
    SCREEN_HEIGHT = screenHeight;
}

void Game::Start()
{
//===========Setup la Grille==============
    const static int GRID_WIDTH = 10;
    const static int GRID_HEIGHT = 10;

    const static int CELL_WIDTH = 32;
    const static int CELL_HEIGHT = 32;
    //Vector2 gridPos = { SCREEN_WIDTH / 2 - (GRID_WIDTH * CELL_WIDTH) / 2 ,SCREEN_HEIGHT / 2 - (GRID_HEIGHT * CELL_HEIGHT) / 2 };
    Vector2 gridPos = { -200,-200 };

    Texture2D tileSprite = LoadTexture("Ressources/TileBackground.png");

    grid = Grid(gridPos, GRID_WIDTH, GRID_HEIGHT, CELL_WIDTH, CELL_HEIGHT); //On génère la grille
    grid.spriteOfTiles = tileSprite;
    grid.Start();

//=========Setup la camera==========
    cam.position = { 250,250,250 };
    cam.target = { 0,0,0 }; //Regarde au centre du monde 
    cam.up = { 0,1,0 };
    cam.fovy = 45;
    cam.projection = CAMERA_PERSPECTIVE;
    

//=========Setup les obstacles==========
    Texture2D obstacleSprite = LoadTexture("Ressources/Obstacle.png");
    obstacles.push_back(new Obstacle({ 4,4 }, obstacleSprite));
    obstacles.push_back(new Obstacle({ 2,2 }, obstacleSprite));
    obstacles.push_back(new Obstacle({ 8,3 }, obstacleSprite));
    obstacles.push_back(new Obstacle({ 8,5 }, obstacleSprite));
    obstacles.push_back(new Obstacle({ 3,8 }, obstacleSprite));

    for each (Obstacle * obstacle in obstacles)
    {
        obstacle->Init();
    }


//=============Controllers Setup============

    controllers.emplace_back(new PlayerController());   //Rajoute un player
   // controllers.emplace_back(Ennemy());             //Rajoute un ennemy (old)

    for (auto i = controllers.begin(); i != controllers.end(); i++)
    {
        (*i)->Start();
        (*i)->SetGrid(&grid);

    }

//=============Setup Cursor===========
    cursor.Start();

//============Setup elements in game==============
    for (int i = 0; i < player.GetPawns()->size(); i++)
    {
        elementsInGame.push_back(&player.GetPawns()->at(i));
    }
    for (int i = 0; i < ennemy.GetPawns()->size(); i++)
    {
        elementsInGame.push_back(&ennemy.GetPawns()->at(i));
    }

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
    turnManager.AddSomethingMakeTurn(&player);
    turnManager.AddSomethingMakeTurn(&ennemy);
    turnManager.Start();



}

void Game::Update()
{
    turnManager.Update();
    grid.Update();

    for (auto i = controllers.begin(); i != controllers.end(); i++)
    {
        (*i)->Update();
    }

    cursor.Updtate();


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
    BeginMode3D(cam);

    DrawGrid(32, 32);
    grid.Draw();
    for each (Actor* obstacle in obstacles)
    {
        obstacle->Draw();
    }

    for (auto i = controllers.begin(); i != controllers.end(); i++)
    {
        (*i)->Draw();
    }

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
