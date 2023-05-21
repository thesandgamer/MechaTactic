#pragma once
#include "raylib.h"
#include "raymath.h"
#include "Actor.h"

//Class pour gérer la camera, la bouger, la faire tourner, zoomer dézommer,...
//La camera doit avoir:
//	la camera
//	la position du tout
//	Une rotation / où ça regarde
//	Un handle des inputs
//	Une fonction Zoom Dezoom
//	Une fonction move en dragant l'écran
//	Une fonction move avec touches
//	Une fonction move qui bouge la position

enum CameraType
{
	TopDown,
	Iso
};

class CameraActor: public Actor
{
public:
	CameraActor();
	CameraActor(Vector3 basePos);
	~CameraActor();

	void Init();
	void Draw();
	void Update();

	Camera& GetCamera() { return cam; }

	void SetCameraType(CameraType newType);

private:
	Camera cam{ 0 };

	float targetDistance;
	Vector2 angle;

	Vector3 baseLoc;

	CameraType camType { TopDown };

	
};

