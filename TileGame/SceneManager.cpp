#include "SceneManager.h"
#include "Game.h"
#include "SceneParent.h"

void SceneManager::init()
{
	Game* GameScene = new Game();
	scenes.push_back(GameScene);
}

void SceneManager::start() const
{
	scenes.at(currentScene)->start();
}

void SceneManager::update() const
{
	scenes.at(currentScene)->update();
	scenes.at(currentScene)->draw();
}

void SceneManager::drawUi() const
{
	scenes.at(currentScene)->drawUi();
}

void SceneManager::close() const
{
	scenes.at(currentScene)->close();
}

void SceneManager::changeScene(const int sceneIndexP)
{
	close();
	currentScene = sceneIndexP;
	start();
}


const SceneParent& SceneManager::getCurrentScene() const
{
	return *scenes.at(currentScene);
}
