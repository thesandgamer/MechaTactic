#include "CollisionManager.h"

CollisionManager* CollisionManager::instance{ nullptr };	//Instancie l'objet

void CollisionManager::Start()
{
}

void CollisionManager::Update()
{
	ProcessColisions();
}

void CollisionManager::Draw()
{
	for (auto i = colliders.begin(); i < colliders.end(); i++)
	{
		(*i)->Draw();
	}
}

void CollisionManager::AddCollider(P_Collision* collider)
{
	 colliders.push_back(collider);
}

void CollisionManager::RemoveCollider(P_Collision* colliderToRemove)
{
	if (colliderToRemove == nullptr) return;
	if (std::find(colliders.begin(), colliders.end(), colliderToRemove) != colliders.end())
	{
		colliders.erase(std::find(colliders.begin(), colliders.end(), colliderToRemove));
	}
	
}


//Rayon qui touche ou pas: return si il touche quelque chose, la position o� il touche, et ce qu'il touche
bool CollisionManager::DoRayCollision(RaycastCollision* ray, RaycastHit& outHit)
{
	RaycastHit infos = {false};
	outHit.Clean();
	for  (P_Collision * collider : colliders) //On va r�cup�rer un collider et regarder si il collide avec les autres collider
	{
		if (collider == ray) continue;
		if (collider == nullptr) continue;

		switch (collider->collisionType)
		{
		case BoxCollider:
			RayHitInfo inf = GetRayCollisionBox(ray->GetRay(), dynamic_cast<BoxCollision*>(collider)->GetBoundingBox());
			if (inf.hit && inf.distance < outHit.hitDistance)
			{
				outHit.hit = inf.hit;
				outHit.hitDistance = inf.distance;
				outHit.hitNormal = inf.normal;
				outHit.hitPosition = inf.position;
				outHit.hitCollider = collider;
			}


			break;

		case SphereCollider:
			inf = (GetRayCollisionSphere(ray->GetRay(),
				dynamic_cast<SphereCollision*>(collider)->GetCollider().Center,
				dynamic_cast<SphereCollision*>(collider)->GetCollider().Radius));

			if (inf.hit && inf.distance < outHit.hitDistance)
			{
				outHit.hit = inf.hit;
				outHit.hitDistance = inf.distance;
				outHit.hitNormal = inf.normal;
				outHit.hitPosition = inf.position;
				outHit.hitCollider = collider;
			}		
			break;

		}

	}
	if (outHit.hit && abs(outHit.hitDistance) < ray->GetLength())
	{
		return true;
	}
	return false;
}

void CollisionManager::ProcessColisions()
{
	for  (P_Collision* collider : colliders) //On va r�cup�rer un collider et regarder si il collide avec les autres collider
	{
		if (!collider->checkingCollision)continue;
		//++ToDo: checker si les deux collider ont le m�me parent, ou si l'un est parent de l'autre, et avoir un bool pour savoir si on veut d�sactiver les collisons entre eux
		switch (collider->collisionType)
		{
		case BoxCollider:
			DoCollisionBoxsCheck(dynamic_cast<BoxCollision*>(collider));
		break;

		case RayCollider:
			DoRayBoxCollisionCheck(dynamic_cast<RaycastCollision*>(collider));	//Si c'est le rayon qui check ses collisions
		break;

		case SphereCollider:
			DoSphereBoxCollisionCheck(dynamic_cast<SphereCollision*>(collider));
		break;

		default:
			break;
		}
	}
}


/// <summary>
/// On check les collisions entre des BB et d'autres BB
/// </summary>
/// <param name="colliderToCheck"></param>
void CollisionManager::DoCollisionBoxsCheck(BoxCollision* colliderToCheck)
{
	for  (P_Collision* collider : colliders)
	{
		if (colliderToCheck == collider) continue;
		if (colliderToCheck->collideWithLayer != collider->layer) continue;	//Si le collider ne collide pas avec le layer de l'autre objet
		bool collide = false;
		switch (collider->collisionType)
		{
		case BoxCollider:	//Si l'autre est une boite
			collide = CheckCollisionBoxes(colliderToCheck->GetBoundingBox(), dynamic_cast<BoxCollision*>(collider)->GetBoundingBox());
			break;
		case RayCollider:	//Si l'autre est un rayon
			RayHitInfo hitinfo = GetRayCollisionBox(dynamic_cast<RaycastCollision*>(collider)->GetRay(), colliderToCheck->GetBoundingBox());
			collide = hitinfo.hit && abs( hitinfo.distance) <= dynamic_cast<RaycastCollision*>(collider)->GetLength();
			break;
		case SphereCollider:	//Si l'autre est une sph�re
			collide = CheckCollisionBoxSphere(colliderToCheck->GetBoundingBox(),
				dynamic_cast<SphereCollision*>(collider)->GetCollider().Center, dynamic_cast<SphereCollision*>(collider)->GetCollider().Radius);
			break;
		default:
			break;
		}
		InsertCollision(collide, collider, colliderToCheck);

	
	
	}
}

void CollisionManager::DoRayBoxCollisionCheck(RaycastCollision* colliderToCheck)
{
	for  (P_Collision * collider : colliders)
	{
		if (colliderToCheck == collider) continue;
		if (colliderToCheck->collideWithLayer != collider->layer) continue;
		bool collide = false;

		switch (collider->collisionType)
		{

		case BoxCollider:
			RayHitInfo hitinfo = GetRayCollisionBox(colliderToCheck->GetRay(), dynamic_cast<BoxCollision*>(collider)->GetBoundingBox());
			collide = hitinfo.hit && abs( hitinfo.distance) <= colliderToCheck->GetLength();
			break;

		case SphereCollider:
			RayHitInfo hit = GetRayCollisionSphere(colliderToCheck->GetRay(), 
				dynamic_cast<SphereCollision*>(collider)->GetCollider().Center, 
				dynamic_cast<SphereCollision*>(collider)->GetCollider().Radius);
			collide = hit.hit && abs(hit.distance) <= colliderToCheck->GetLength();
			break;

		default:
			break;

		}		
		InsertCollision(collide, collider, colliderToCheck);

	}
}

void CollisionManager::DoSphereBoxCollisionCheck(SphereCollision* colliderToCheck)//Une sph�re va check les autres collisons
{
	for  (P_Collision * collider : colliders)
	{
		if (colliderToCheck == collider) continue;
		if (colliderToCheck->collideWithLayer != collider->layer) continue;
		bool collide{ false };

		switch (collider->collisionType)
		{

		case BoxCollider:
			collide = CheckCollisionBoxSphere(dynamic_cast<BoxCollision*>(collider)->GetBoundingBox(),
				colliderToCheck->GetCollider().Center, colliderToCheck->GetCollider().Radius);
			if (collide)
			{
				//std::cout << "col: "<< collider->layer << std::endl;
			}
			break;

		case RayCollider:
			RayHitInfo hit = GetRayCollisionSphere(dynamic_cast<RaycastCollision*>(collider)->GetRay(),
				colliderToCheck->GetCollider().Center, colliderToCheck->GetCollider().Radius);
			collide = hit.hit && abs(hit.distance) <= dynamic_cast<RaycastCollision*>(collider)->GetLength();

			break;

		case SphereCollider:
			collide = CheckCollisionSpheres(colliderToCheck->GetCollider().Center, colliderToCheck->GetCollider().Radius,
				dynamic_cast<SphereCollision*>(collider)->GetCollider().Center, dynamic_cast<SphereCollision*>(collider)->GetCollider().Radius);
			break;

		default:
			break;

		}
		InsertCollision(collide, collider, colliderToCheck);

	}
}

void CollisionManager::InsertCollision(bool insert, P_Collision* collider, P_Collision* colliderToCheck)
{
	bool colliderToCheckAlreadyInCollider = std::find(collider->collisions.begin(), collider->collisions.end(), colliderToCheck) != collider->collisions.end();
	bool colliderAlreadyInColliderToCheck = std::find(colliderToCheck->collisions.begin(), colliderToCheck->collisions.end(), collider) != colliderToCheck->collisions.end();
	if (insert)
	{
		if (!colliderAlreadyInColliderToCheck)
		{
			colliderToCheck->collisions.insert(collider);
		}
		if (!colliderToCheckAlreadyInCollider)
		{
			//collider->collisions.insert(colliderToCheck);
		}
	}
	else
	{
		
		colliderToCheck->collisions.erase(collider);
		//collider->collisions.erase(colliderToCheck);

	}
}


