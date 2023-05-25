#pragma once
#include "raylib.h"
#include "raymath.h"
#include "Actor.h"
#include "LifeManager.h"

//
// Créer une barre de vie au desus d'un actor
// Actor relié
// Offset
//	Box pour chaque PV
// Box qui englobe les tous les box de PV
// Lien avec LifeManager
//

//++ToDo: mieux architecturer ça avec des events pour listen la vie à laquelle elle se lie

class InGameLifeBar
{
public:
	InGameLifeBar();
	InGameLifeBar(Actor* onActor);
	InGameLifeBar(LifeManager* lifeManager);
	InGameLifeBar(Actor* onActor,LifeManager* lifeManager,Vector3 Offset);
	InGameLifeBar(Actor* onActor,Vector3 Offset);
	InGameLifeBar(Vector3 Offset);
	~InGameLifeBar();

	void Draw();
	void Update();

	void LinkTo(LifeManager* lifeManager, Actor* actor);


private:
	void Init();

	Actor* actorOn{nullptr};
	LifeManager* lifeLinkTo{nullptr};
	Vector3 offset{0,0,0};

	Transform transf{};

	Vector2 spacerSize{ 6,6 };
	Vector2 lifeBlocSize{ 6,16 };

};

