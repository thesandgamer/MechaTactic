#include "Engine.h"

#include <iostream>

#include "Game.h"
#include "Utility.h"


bool Engine::isRunning{ false };

void Engine::run()
{
	isRunning = init();
	if (!isRunning)
	{
		std::cout << "Error on window and renderer init" << "\n";
		close();
		return;
	}

	sceneManager.start();

    std::srand(std::time(nullptr));

    //Créer un écran et on met les fps à 60
    const std::string windowName = "Mecha Tactic";
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, windowName.c_str());

    //ToggleFullscreen();
    SetWindowPosition(0, 10);
    SetTargetFPS(60);

    Utility::GetInstance()->Start();

    Game::instance().SetupScreen(SCREEN_WIDTH, SCREEN_HEIGHT);

    Game::instance().Start();

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        Game::instance().Update();
        Game::instance().Draw();
    }

    close();

}

void Engine::quitGame()
{
}

bool Engine::init()
{
	return false;
}

void Engine::close()
{
    sceneManager.close();

    Game::instance().clean();

    Utility::GetInstance()->Unload();

    CloseWindow();
}
