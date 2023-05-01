#include "CameraActor.h"

CameraActor::CameraActor(): Actor()
{
    cam.position = { 250,250,250 };

}

CameraActor::CameraActor(Vector3 basePos) : Actor()
{
    cam.position = basePos;

}

CameraActor::~CameraActor()
{

}

void CameraActor::Init()
{
    //=========Setup la camera==========
    cam.target = { 0,0,0 }; //Regarde au centre du monde 
    cam.up = { 0,1,0 };
    cam.fovy = 45;
    cam.projection = CAMERA_PERSPECTIVE;

    SetCameraMode(cam, CAMERA_FREE);
}

void CameraActor::Draw()
{
}

void CameraActor::Update()
{
    float mouseWheelMove = GetMouseWheelMove();
    //UpdateCamera(&cam);
    //Zoom et dezoom de la camera
    //Déplacement de la camera
    //Tourner la camera

    

}


