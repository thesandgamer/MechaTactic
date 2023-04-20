#pragma once
#include <iostream>
#include <string>
#include "raylib.h"

#include "IInformationPasseur.h"

using std::string;

class InformationDisplay
{
public:
	InformationDisplay(string titleP);
	InformationDisplay();

	string GetTitle() { return title; }
	void SetTitle(string titleP) { title = titleP; }

	void SetPos(Vector3* pos);
	Vector3 GetPos() { return *position; }

	InformationDisplay(const InformationDisplay& other)
	{
		operator=(other);

	}
	InformationDisplay& operator=(const InformationDisplay& other)
	{
		this->title = other.title;
		this->position = other.position;
	}
	Vector3* position;
	IInformationPasseur* infPasseur;



private:
	string title;

		
};

//L'idée va être que quand on va passer la souris sur un élément de jeu, ça affiche(à droite en texte pour faire simple) les informations dessus, par exemple on passe la souris sur un ennemi et ça va marquer ce qu'il peut faire,
//ou marquer sa range d'attaque(ou juste la surligner), pareil pour les tiles de base, 

