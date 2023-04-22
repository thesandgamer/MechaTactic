#include "TurnsManager.h"
#include "Game.h"

TurnsManager::TurnsManager() : haveTurn{ nullptr }, actual(0)
{
}

TurnsManager::~TurnsManager()
{
}

void TurnsManager::MakeTurnList(vector<ITurn*> pawnInGame)
{
}

void TurnsManager::Start()
{
	//----------Set Ui----------
	Texture2D bandeauSprite = LoadTexture("Ressources/Bandeau.png");
	Vector2 pos = { 0, Game::instance().SCREEN_HEIGHT / 2 };
	endTurnBandeau = BandeauTexte(bandeauSprite,pos,1.5f);

	//----------
	haveTurn = allControllers.at(0);//Le premier mecha de la liste à le tour
	MakeTurns();
}

void TurnsManager::Update()
{
	Game::instance().GetGrid()->CalculateObstacles(); //Pas mettre ça ici 

	endTurnBandeau.Update();

	if (haveTurn != nullptr) //Si quelqu'un existe
	{
		if (haveTurn->HaveEndTurn())//Si il à finit son tour
		{
			//Passe au suivant 
			if (actual < allControllers.size()-1)
			{
				actual++;
			}
			else
			{
				actual = 0;
			}
			MakeTurns();
		}
	}
}

void TurnsManager::MakeTurns()
{
	endTurnBandeau.SetText(allControllers.at(actual)->GetName());
	endTurnBandeau.DisplayBandeau();

	haveTurn = allControllers.at(actual);	//Le controller qui va jouer va être celui à l'actuel
	haveTurn->StartTurn();

}

void TurnsManager::DrawUi()
{
	endTurnBandeau.Draw();

}

void TurnsManager::AddSomethingMakeTurn(ITurn* turn)
{
	allControllers.push_back(turn);
}
