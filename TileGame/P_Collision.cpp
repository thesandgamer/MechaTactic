#include "P_Collision.h"
#include "CollisionManager.h"



P_Collision::P_Collision(CollisionType type) : collisionType{ type }
{
	CollisionManager::GetInstance()->AddCollider(this);//Rajoute tout seul la boite de collisoon au manager � la cr�ation
}

P_Collision::~P_Collision()
{
	CollisionManager::GetInstance()->RemoveCollider(this);//On enl�ve le pointeur de la liste des colliders
	collisions.clear();
	Transform = nullptr;
}

void P_Collision::Draw()
{
}

bool P_Collision::IsColliding()
{

	if (collisions.size() > 0)	//Si on � des collisions
	{
		for  (P_Collision* col : collisions)//Pour chaque collider avec lequel on collide
		{
			if (!col->trigger)//Si il ne trigger pas
			{
				return true;//Il y a collision
			}
		}
	}
	return false;//Sinon si pas de collision o� que des trigger pas de colliding
}

void P_Collision::SetParent(Actor* parentP)
{
	Parent = parentP;
	Transform = parentP->GetTransformPointer();
}


