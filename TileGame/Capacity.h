#pragma once

//Classe parente de capacit�e, va se rajouter sur un mecha
// 
// Va avoir deux enfants: passive et active capacity
// Va permettre d'afficher
// Les capacit�s actives: bouton, on clique dessus 

class Capacity
{
public:

	virtual void Init();
	virtual void DrawUi();
	virtual void Draw() ;
	virtual void Update() ;

	virtual void DrawPossibleZone();

private:

};

