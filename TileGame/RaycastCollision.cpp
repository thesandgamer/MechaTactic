#include "RaycastCollision.h"

RaycastCollision::RaycastCollision() :P_Collision(RayCollider)
{
}

RaycastCollision::RaycastCollision(Vector3 directionP, float lengthP) :P_Collision(RayCollider), direction(directionP), length{ lengthP }
{
}

RaycastCollision::~RaycastCollision()
{
}

void RaycastCollision::Draw()
{
    DrawRay(GetRay(),length, (IsColliding()) ? RED : GREEN);
}

Ray RaycastCollision::GetRay()
{
    if (Transform == NULL) return { Offset.translation,direction };
    //return {Vector3Add( Transform->translation, Offset.translation),Vector3RotateByQuaternion(direction,Transform->rotation) };
    return {Vector3Add( Transform->translation, Offset.translation),direction };
}

void RaycastCollision::SetPosition(Vector3 pos)
{
    Offset.translation = pos;
}
