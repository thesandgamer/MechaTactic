#pragma once
#include "SceneManager.h"
#include <SDL.h>

#include "CameraActor.h"

static constexpr int SCREEN_WIDTH = 1920;
static constexpr int SCREEN_HEIGHT = 1080;

class Engine
{
public:
	void run();
	static bool isRunning;
	static void quitGame();

	static CameraActor* getCameraActor();

private:
	bool init();
	void close() const;
	SceneManager sceneManager;



};

