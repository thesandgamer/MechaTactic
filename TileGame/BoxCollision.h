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


private:
	BoundingBox boundingBox;

	Model* modelToBoxing{ nullptr };



	//++ToDo trouver un moyen de cr�er une box avec comme param une pointeur vers une valeur
};


