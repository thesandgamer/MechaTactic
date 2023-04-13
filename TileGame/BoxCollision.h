#pragma once
#include "P_Collision.h"


//++ToDo faire un parent component avec une fonction virtuelle de start draw update


class BoxCollision :
    public P_Collision
{
public:
	BoxCollision();
	BoxCollision(Vector3 sizeP);
	BoxCollision(Model*  model);

	void Init();
	void Draw() override;

	BoundingBox GetBoundingBox(); //++Todo Renvoyer un pointeur de bounding box

	void Test() {};

	Model* modelToBoxing{ nullptr };

	BoxCollision& operator=(const BoxCollision& other)
	{
		this->boundingBox = other.boundingBox;
		this->modelToBoxing = other.modelToBoxing;
		this->collideWithLayer = other.collideWithLayer;
		this->collisions = other.collisions;
		this->collisionType = other.collisionType;
		this->drawCollision = other.drawCollision;
		return *this;
	}


private:
	BoundingBox boundingBox;




	//++ToDo trouver un moyen de créer une box avec comme param une pointeur vers une valeur
};


