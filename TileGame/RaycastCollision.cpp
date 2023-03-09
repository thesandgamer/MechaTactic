#include "RaycastCollision.h"

RaycastCollision::RaycastCollision() :P_Collision()
{
    collisionType = RayCollider;
}

RaycastCollision::RaycastCollision(Vector3 directionP, float lengthP) :P_Collision(), direction(directionP), length{ lengthP }
{
    collisionType = RayCollider;
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
    if (Transform == NULL) return {0,0,0};
    //return {Vector3Add( Transform->translation, Offset.translation),Vector3RotateByQuaternion(direction,Transform->rotation) };
    return {Vector3Add( Transform->translation, Offset.translation),direction };
}
