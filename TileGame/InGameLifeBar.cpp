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
		Vector2 posOnScreen = GetWorldToScreen(pos, Game::instance().cam.GetCamera());

		LifeData data = lifeLinkTo->ReturnLifeData();

		//Set la taille de la boite qui englobe les points de vie
			//largeur: Taille des bloc de pv * nombre de pv max + taille des spacer * nombre de points de vie + spacer en plus 
		float width = (lifeBlocSize.x* data.maxLife + spacerSize.x*(data.maxLife) + spacerSize.x);
		float height = (lifeBlocSize.y + spacerSize.y);
		Rectangle frame = { posOnScreen.x - width / 2 ,posOnScreen.y ,width, height };

		DrawRectangle(frame.x, frame.y, frame.width, frame.height, DARKGRAY);//Remplacer la taille/pos en fonction du nombre max de pv


		for (int i = 0; i < (int)data.currentLife; i++)
		{					//Position d'orinigne + iTailleSpace + iTailleBlocDeVie + taille spacer pour décaler le x
			DrawRectangle( (frame.x + (i* spacerSize.x) + (i * lifeBlocSize.x) + spacerSize.x)  ,
				posOnScreen.y + spacerSize.y/2, 
				lifeBlocSize.x, lifeBlocSize.y, GREEN);//Remplacer la taille/pos en fonction du nombre max de pv
		}

	}
}

void InGameLifeBar::Update()
{
}


void InGameLifeBar::Init()
{
	

}
