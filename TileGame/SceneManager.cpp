#include "SceneManager.h"

void SceneManager::start()
{
	scenes.at(currentScene).start();
}

void SceneManager::update()
{
	scenes.at(currentScene).update();
}

void SceneManager::close()
{
	scenes.at(currentScene).close();
}

void SceneManager::changeScene(const int sceneIndexP)
{
	close();
	currentScene = sceneIndexP;
	start();
}
