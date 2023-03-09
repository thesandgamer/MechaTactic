#include "P_Collision.h"
#include "CollisionManager.h"



P_Collision::P_Collision()
{
	CollisionManager::GetInstance()->AddCollider(this);//Rajoute tout seul la boite de collisoon au manager � la cr�ation
}

P_Collision::~P_Collision()
{
	CollisionManager::GetInstance()->RemoveCollider(this);//On enl�ve le pointeur de la liste des colliders
	collisions.clear();
	Transform = nullptr;
}

bool P_Collision::IsColliding()
{

	if (collisions.size() > 0)	//Si on � des collisions
	{
		for each (P_Collision* col in collisions)//Pour chaque collider avec lequel on collide
		{
			if (!col->trigger)//Si il ne trigger pas
			{
				return true;//Il y a collision
			}
		}
	}
	return false;//Sinob si pas de collision o� que des trigger pas de colliding
}
