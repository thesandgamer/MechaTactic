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

#include "MushMech.h"
#include "TreeMech.h"

#include "FX_Sprite.h"
#include "SceneParent.h"


//++ToDo: faire en sorte que les info s'affichent en fonction de l'objet touché par le rayon

class Game : public SceneParent
{

public:

	Game() = default;

	void start() override;
	void update() override;
	void draw() override;
	void drawUi() override;

	void clean();

	Grid* getGrid() { return &grid; }

	vector<Actor*> getElementsInGame() { return elementsInGame; }


	CameraActor cam; // Faire en sorte qu'il y ait plusieurs camera, un par player controller

	bool somethingAlreadyHere(Vector2 pos);	//++ToDo: mettre ça autre part

	void createVfx(FX_Sprite* vfx);

	void removeVfx(FX_Sprite* vfToRemove);



private:

	//---Gère les controllers
	TurnsManager turnManager;
	vector<Controller*> controllers;	//++ToDo: Remplacer ça par unique pointer



	//-----Pour lagrille
	Grid grid;

	Cursor cursor;

	/// <summary>
	/// For elements in game: Mechs and obstacle for now
	/// </summary>
	vector<Actor*> elementsInGame;

	vector<Obstacle*> obstacles;

	vector <FX_Sprite*> vfxs;




//========On va gérer le display des informations
	/* Mettre la feature dans le player controller
	InformationDisplayUi* infoUi;
	vector<InformationDisplay*> informations;

	*/



};

