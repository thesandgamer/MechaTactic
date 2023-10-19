#pragma once
#include <vector>
#include "SceneParent.h"

/// <summary>
/// Pour gérer les différentes scènes
/// </summary>

class SceneManager
{
public:
	void init();
	void start() const;
	void update() const;
	void drawUi() const;
	void close() const;

	void changeScene(const int sceneIndexP);

	const SceneParent& getCurrentScene() const;

	//Handle les différentes scènes
	std::vector<SceneParent*> scenes;

private:
	int currentScene = 0;
};

