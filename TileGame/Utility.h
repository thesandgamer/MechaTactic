#pragma once
#include "raylib.h"
#include <vector>

int const screenWidth = 1920;
int const screenHeight = 1080;

class Utility
{
	//--------------Make it a singleton------------------
private:
	Utility() {};
	static Utility* instance;

public:
	Utility(const Utility& obj) = delete;
	void operator=(const Utility&) = delete;

	static Utility* GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new Utility();
		}
		return instance;
	}

public:

	void Start();

	Texture2D champiTexture{};// = LoadTexture("../resources/Dot.png");
	Texture2D treeTexture{};

	Shader* shader{nullptr};

	Model ChampiModel{};
	Model TreeModel{};


	void Unload();


};

