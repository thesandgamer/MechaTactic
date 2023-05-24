#include "InGameLifeBar.h"
#include "Game.h"

InGameLifeBar::InGameLifeBar()
{
}

InGameLifeBar::InGameLifeBar(Actor* onActor): actorOn(onActor)
{
}

InGameLifeBar::InGameLifeBar(LifeManager* lifeManager): lifeLinkTo(lifeManager)
{
}

InGameLifeBar::InGameLifeBar(Actor* onActor, LifeManager* lifeManager, Vector3 Offset): actorOn(onActor), lifeLinkTo(lifeManager), offset{Offset}
{
}

InGameLifeBar::~InGameLifeBar()
{
}

void InGameLifeBar::Draw()
{
	Vector3 pos = Vector3Add(actorOn->GetPosition(), offset);
	if (lifeLinkTo != nullptr)
	{
		LifeData data = lifeLinkTo->ReturnLifeData();
		float width = (lifeBlocSize.x* data.maxLife + spacerSize.x*(data.maxLife+1) );
		float height = (lifeBlocSize.y + spacerSize.y);

		Vector2 posOnScreen = GetWorldToScreen(pos, Game::instance().cam.GetCamera());
		DrawRectangle(posOnScreen.x, posOnScreen.y, width, height, DARKGRAY);//Remplacer la taille/pos en fonction du nombre max de pv

		for (int i = 0; i < (int)data.currentLife; i++)
		{
			DrawRectangle(posOnScreen.x + i* spacerSize.x + i * lifeBlocSize.x + spacerSize.x, posOnScreen.y +spacerSize.y/2, lifeBlocSize.x, lifeBlocSize.y, GREEN);//Remplacer la taille/pos en fonction du nombre max de pv
		}

	}
}

void InGameLifeBar::Update()
{
}


void InGameLifeBar::Init()
{
	

}
