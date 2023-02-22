#pragma once
#include "Actor.h"
#include "Player.h"
#include "Ennemy.h"
#include "Grid.h"
#include "Button.h"
#include "InformationDisplayUi.h"
#include "TurnsManager.h"
#include "Cursor.h"
#include "Obstacle.h"

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
	Game() : player{ Player() }, SCREEN_WIDTH{ -1 }, SCREEN_HEIGHT{ -1 }, infoUi{nullptr} {};



public:
	void SetupScreen( int screenwidth,  int screenHeight);

	void Start();
	void Update();
	void Draw();
	void DrawUi();

	Grid* GetGrid() { return &grid; }

	vector<Actor*> GetElementsInGame() { return elementsInGame; }

	Player* GetPlayer() { return &player; }

	int  SCREEN_WIDTH;
	int  SCREEN_HEIGHT;

private:


	TurnsManager turnManager;
	Player player;
	Ennemy ennemy;
	Grid grid;

	Cursor cursor;

	vector<Actor*> elementsInGame;

	vector<Obstacle*> obstacles;



//========On va gérer le display des informations
	InformationDisplayUi* infoUi;
	vector<InformationDisplay*> informations;





};

