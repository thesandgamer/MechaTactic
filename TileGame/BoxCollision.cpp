#include "BoxCollision.h"


BoxCollision::BoxCollision()
{
}

BoxCollision::BoxCollision(Vector3 sizeP) : P_Collision()
{
	Offset.scale = sizeP;


	
		
	

	
}

BoxCollision::BoxCollision(Model* model)
{
	modelToBoxing = model;
}



void BoxCollision::Init()
{
	if (modelToBoxing == nullptr)	//Si c'est une simple boite de collision avec la scale
	{
		boundingBox = { 
	/*Min*/	Vector3{(Transform->translation.x + Offset.translation.x) - (Transform->scale.x * Offset.scale.x / 2) ,
					 (Transform->translation.y + Offset.translation.y) - (Transform->scale.y * Offset.scale.y / 2),
					 (Transform->translation.z + Offset.translation.z) - (Transform->scale.z * Offset.scale.z / 2)},

	/*Max*/	Vector3{(Transform->translation.x + Offset.translation.x) + (Transform->scale.x * Offset.scale.x / 2) ,
					 (Transform->translation.y + Offset.translation.y) + (Transform->scale.y * Offset.scale.y / 2) ,
					 (Transform->translation.z + Offset.translation.z) + (Transform->scale.z * Offset.scale.z / 2) } };
	}
	else
	{
		BoundingBox box = GetModelBoundingBox(*modelToBoxing);
		//boundingBox = box;
		
		boundingBox = {
			{	box.min.x + (Transform->translation.x + Offset.translation.x),
				box.min.y + (Transform->translation.y + Offset.translation.y),
				box.min.z + (Transform->translation.z + Offset.translation.z)
			},
			{
				box.max.x + (Transform->translation.x + Offset.translation.x),
				box.max.y + (Transform->translation.y + Offset.translation.y),
				box.max.z + (Transform->translation.z + Offset.translation.z)
			}
		};
	}
	
}

void BoxCollision::Draw()
{
	DrawBoundingBox(GetBoundingBox(), (IsColliding()) ? RED : GREEN);
}

BoundingBox BoxCollision::GetBoundingBox()
{
	Init();
	return boundingBox;
}
