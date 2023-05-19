#pragma once
#include "Actor.h"
#include "Grid.h"
#include "Button.h"
#include "InformationDisplayUi.h"
#include "TurnsManager.h"
#include "Cursor.h"
#include "Obstacle.h"
#include "CameraActor.h"

#include "Controller.h"
#include "PlayerController.h"
#include "EnnemyController.h"


//++ToDo: faire en sorte que les info s'affichent en fonction de l'objet touché par le rayon

class Game
{
public:
	static Game& instance()
	{
		static Game inst;
		return inst;
	}

	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	Game(Game&&) = delete;
	Game& operator=(Game&&) = delete;
private:
	Game() : SCREEN_WIDTH{ -1 }, SCREEN_HEIGHT{ -1 } {};// infoUi{nullptr} {};



public:
	void SetupScreen( int screenwidth,  int screenHeight);

	void Start();
	void Update();
	void Draw();
	void DrawUi();

	void Clean();

	Grid* GetGrid() { return &grid; }

	vector<Actor*> GetElementsInGame() { return elementsInGame; }


	CameraActor cam; // Faire en sorte qu'il y ait plusieurs camera, un par player controller

	bool SomethingAlreadyHere(Vector2 pos);


	int  SCREEN_WIDTH;
	int  SCREEN_HEIGHT;

private:

	//---Gère les controllers
	TurnsManager turnManager;
	vector<Controller*> controllers;	//++ToDo: Remplacer ça par unique pointer



	//-----Pour lagrille
	Grid grid;

	Cursor cursor;

	vector<Actor*> elementsInGame;

	vector<Obstacle*> obstacles;




//========On va gérer le display des informations
	/* Mettre la feature dans le player controller
	InformationDisplayUi* infoUi;
	vector<InformationDisplay*> informations;

	*/



};

