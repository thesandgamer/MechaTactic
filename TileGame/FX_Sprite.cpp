#include "FX_Sprite.h"
#include "Game.h"

/**
/// Texture2D / int / int / Vec3
**/
FX_Sprite::FX_Sprite()
{
    Init();
}

/// <summary>
/// 
/// </summary>
/// <param name="image"></param>
/// <param name="NumberOfFrames"></param>
/// <param name="speed"></param>
/// <param name="pos"></param>
FX_Sprite::FX_Sprite(Texture2D image, int NumberOfFrames, float speed, Vector3 pos): sprite(image), NbFrames(NumberOfFrames), framesSpeed(speed)
{
    posOnScreen = GetWorldToScreen(pos, Game::instance().cam.GetCamera());
    //posOnScreen = { 1,10 };
    Init();
}


FX_Sprite::~FX_Sprite()
{
}

void FX_Sprite::Init()
{
    
    frameRec = { 0.0f, 0.0f, (float)sprite.width / NbFrames, (float)sprite.height };
}

void FX_Sprite::Update()
{
    framesCounter++;

    if (framesCounter >= (60 / framesSpeed))
    {
        framesCounter = 0;
        currentFrame++;

        if (currentFrame > NbFrames - 1)
        {
            //currentFrame = 0;
            //Ou
            delete this;
        }

        frameRec.x = (float)currentFrame * (float)sprite.width / NbFrames;
    }

}

void FX_Sprite::Draw()
{
    DrawTextureRec(sprite, frameRec, { posOnScreen.x - (sprite.width / NbFrames) /2 ,posOnScreen.y - sprite.height  }, WHITE);
}
