#pragma once
#include "SceneManager.h"

class Engine
{
public:
	void run();
	static bool isRunning;
	static void quitGame();

private:
	bool init();
	void close();
	SceneManager sceneManager;

	constexpr int SCREEN_WIDTH = 1920;
	constexpr int SCREEN_HEIGHT = 1080;

};

