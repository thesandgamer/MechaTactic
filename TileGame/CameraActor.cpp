#include "CameraActor.h"

CameraActor::CameraActor(): Actor()
{
    transform.translation = { 0,800,1 };

}

CameraActor::CameraActor(Vector3 basePos) : Actor()
{
    transform.translation = basePos;

}

CameraActor::~CameraActor()
{

}

void CameraActor::Init()
{
    cam.position = transform.translation;

    //=========Setup la camera==========
   // cam.target = { transform.translation.x,transform.translation.y-500,transform.translation.z }; //Regarde au centre du monde 
    cam.target = { 0,0,0 };
    cam.up = { 0,1,0 };
    cam.fovy = 45;
    cam.projection = CAMERA_PERSPECTIVE;

   // SetCameraMode(cam, CAMERA_FREE);
}

void CameraActor::Draw()
{
}

void CameraActor::Update()
{
    float mouseWheelMove = GetMouseWheelMove();
   // UpdateCamera(&cam);
    //Zoom et dezoom de la camera
    //Déplacement de la camera
    //Tourner la camera

    

}


