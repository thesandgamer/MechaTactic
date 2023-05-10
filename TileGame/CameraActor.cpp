#include "CameraActor.h"

CameraActor::CameraActor(): Actor()
{
    transform.translation = {0,400,0 };

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

    switch (camType)
    {
    case TopDown:
        cam.target = { transform.translation.x,transform.translation.y - 800,transform.translation.z - 1 }; 
        break;
    case Iso:
        transform.translation.y += 100;

        transform.translation.x += 250;
        transform.translation.z += 250;
        cam.target = { transform.translation.x - 5,transform.translation.y - 10,transform.translation.z - 5 }; 

        break;
    default:
        break;
    }

    cam.position = transform.translation;


    //=========Setup la camera==========
    //cam.target = { 0,0,0 };
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


void CameraActor:: SetCameraType(CameraType newType)
{
    camType = newType;
    Init();
}

