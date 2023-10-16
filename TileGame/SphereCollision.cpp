#include "SphereCollision.h"

SphereCollision::SphereCollision() : P_Collision(SphereCollider)
{
}

SphereCollision::SphereCollision(float radius) : P_Collision(SphereCollider)
{
    rad = radius;
}

void SphereCollision::Draw()
{
    if (drawCollision)
    {
        if (trigger)
            DrawSphereWires(GetCollider().Center, GetCollider().Radius, 20, 20, (IsColliding()) ? RED : GREEN);
        else
            DrawSphere(GetCollider().Center, GetCollider().Radius, (IsColliding()) ? RED : GREEN);
    }
}
   

Sphere SphereCollision::GetCollider()
{
    return { {Transform->translation.x + Offset.translation.x,
          Transform->translation.y + Offset.translation.y,
          Transform->translation.z + Offset.translation.z },
        rad
    };
}
