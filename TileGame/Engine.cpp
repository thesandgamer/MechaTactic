#include "Engine.h"

#include <iostream>

#include "Game.h"
#include "Utility.h"

Utility* Utility::instance{ nullptr };


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


    //ToggleFullscreen();
    SetWindowPosition(0, 10);
    SetTargetFPS(60);

    Utility::GetInstance()->Start();


    sceneManager.start();

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        sceneManager.update();
    }

    close();

}

void Engine::quitGame()
{
}

CameraActor* Engine::getCameraActor()
{
    return sceneManager.getCurrentScene().getCamera();
}

bool Engine::init()
{
    const std::string windowName = "Mecha Tactic";
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, windowName.c_str());

	return true;
}

void Engine::close() const
{
    sceneManager.close();

    sceneManager.close();

    Utility::GetInstance()->Unload();

    CloseWindow();
}
