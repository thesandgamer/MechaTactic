#pragma once
#include <vector>

#include "SceneParent.h"

/// <summary>
/// Pour g�rer les diff�rentes sc�nes
/// </summary>

class SceneManager
{
public:
	void start();
	void update();
	void close();

	void changeScene(const int sceneIndexP);

	//Handle les diff�rentes sc�nes
	std::vector<SceneParent> scenes;

private:
	int currentScene = 0;
};

