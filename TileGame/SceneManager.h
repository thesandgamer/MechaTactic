#pragma once
#include <vector>

#include "SceneParent.h"

/// <summary>
/// Pour gérer les différentes scènes
/// </summary>

class SceneManager
{
public:
	void start();
	void update();
	void close();

	void changeScene(const int sceneIndexP);

	//Handle les différentes scènes
	std::vector<SceneParent> scenes;

private:
	int currentScene = 0;
};

