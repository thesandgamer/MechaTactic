#include "BandeauTexte.h"
#include "easings.h"


BandeauTexte::BandeauTexte()
{
}

BandeauTexte::BandeauTexte(Texture2D spriteP, Vector2 positionP, float lifeTimeP) : sprite{ spriteP }, position{ positionP },lifeTime{lifeTimeP}, isActive(false)
{
}

BandeauTexte::~BandeauTexte()
{
}

float currentTime;
Color color = WHITE;

void BandeauTexte::Update()
{
	if (!isActive) return;

	if (currentTime <= lifeTime)
	{
		currentTime += GetFrameTime();
		if (color.a < 255)color.a += 15;
		
		/*
		if (color.a < 255)
		{
			std::cout << color.a << std::endl;
			color.a = EaseSineIn(currentTime, color.a, 255, lifeTime);

		}*/

	}
	else
	{
		if (color.a > 0)color.a -=15;
		else
		{
			isActive = false;

		}
	}

}

void BandeauTexte::Draw()
{
	if (!isActive) return;
	if (sprite.width != NULL)
	{
		DrawTexture(sprite, position.x, position.y, color);
		string text = textIn + " Turn";
		DrawText(text.c_str(), sprite.width / 2 - MeasureText(text.c_str(),30)/2, position.y +sprite.height / 2 - 14, 30, color);
	}
}

void BandeauTexte::DisplayBandeau()
{
	color.a = 0;
	currentTime = 0;

	isActive = true;

}

void BandeauTexte::SetText(string text)
{
	std::cout <<"New text: " << text << std::endl;
	textIn = text;
}


