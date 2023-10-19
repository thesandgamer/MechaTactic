#pragma once
#include <vector>
#include "SceneParent.h"

/// <summary>
/// Pour g�rer les diff�rentes sc�nes
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

	//Handle les diff�rentes sc�nes
	std::vector<SceneParent*> scenes;

private:
	int currentScene = 0;
};

