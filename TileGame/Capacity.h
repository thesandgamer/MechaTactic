#pragma once

//Classe parente de capacitée, va se rajouter sur un mecha
// 
// Va avoir deux enfants: passive et active capacity
// Va permettre d'afficher
// Les capacités actives: bouton, on clique dessus 

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

