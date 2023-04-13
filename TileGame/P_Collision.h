#pragma once
#include "raylib.h"
#include "raymath.h"

#include <set>
#include <iostream>
#include <string>


enum CollisionTouching {
	Up =1 <<0,
	Down =1 <<1,
	Front =1 <<2,
	Back = 1 << 3,
	Left = 1 << 4,
	Right =1 <<5,
};

//++ToDo: faire un meilleur système de layer de collision, ou mieux l'utiliser
enum CollisionLayer {
	Layer0 = 1 << 0,
	Layer1 = 1 << 1,
	Layer2 = 1 << 2,
	Layer3 = 1 << 3,
	Layer4 = 1 << 4,
	Layer5 = 1 << 5,

};

enum CollisionType {
	NOONE,
	BoxCollider,
	SphereCollider,
	MeshCollider,
	RayCollider,
};


class P_Collision
{
public:
	P_Collision();
	~P_Collision();

	virtual void Draw();


	CollisionType collisionType{ NOONE };
	bool trigger{false};
	bool checkingCollision{ false };

    Vector3 GetPosition() { return Transform->translation; }

	bool IsColliding();

	void SetParent(Transform* parentTransform) { Transform = parentTransform; }


	//std::set<std::shared_ptr<P_Collision>> collisions{};
	std::set<P_Collision*> collisions{};	//Avec quels autres collisions il collide


	Transform Offset{ {0,0,0},{0,0,0},{1,1,1} };//Offset de transform
	//std::shared_ptr<Transform> Transform{};	//Transform du parent
	Transform* Transform{};	//Transform du parent

	virtual void Test() {};

	CollisionLayer layer{Layer0};
	CollisionLayer collideWithLayer{Layer0};

	std::string id{ "BaseId"};

	bool drawCollision = true;

};

