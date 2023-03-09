#pragma once
#include "ITurn.h"
#include "BandeauTexte.h"
#include <vector>
using std::vector;

class TurnsManager
{
public:
	TurnsManager();
	~TurnsManager();
	void MakeTurnList(vector<ITurn*> pawnInGame);

	void Start();
	void Update();
	void MakeTurns();

	void DrawUi();

	void AddSomethingMakeTurn(ITurn* turn);

private:
	ITurn* haveTurn;
	vector<ITurn*> allControllers;
	vector<ITurn*> turnList;

	int actual;

	BandeauTexte endTurnBandeau;
	
};


//On va stoquer toutes les Interfaces de tours: pointeur
//Fonction: on va trier les élément de ce qui font leur tour en fonction de leur initiative
//On appel cette fonction à chaque début de tour
//Puis on va appeler la fonction turn de l'interface(qui va retourner un true ou un false) qui va faire en sorte que le tour s'active
//Et parei jusqu'a que tout le monde ait fait son tour
//On recommence jusqu'à la fin 

