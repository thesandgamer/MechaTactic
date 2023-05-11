#include "Button.h"
Button::Button()
{
}

Button::Button(Vector2 pos, Texture2D spriteP, float widthP, float heightP):position(pos), sprite(spriteP), width(widthP), height(heightP), state(ButtonState::IDLE), functPrt(nullptr), functPrtInt(nullptr)
{
	drawColor = WHITE;
	mousePos = nullptr;
	value = -1;
}

Button::Button(Vector2 pos, float widthP, float heightP) : position(pos), width(widthP), height(heightP), state(ButtonState::IDLE), functPrt(nullptr), functPrtInt(nullptr)
{
	drawColor = WHITE;
	mousePos = nullptr;
	value = -1;

}

Button::~Button()
{

}

void Button::ButtonCliqued()
{
	TraceLog(LOG_INFO, " Button cliqued");
	drawColor = GRAY;
	CliquedSendFunction();
	CliquedSendFunctionWithInt();
}

void Button::ButtonHovered()
{
}

void Button::Update()
{
	if (!isActive) return;
	mousePos = &GetMousePosition();
	//Check Si la souris est en hover
	if ((position.x < mousePos->x && mousePos->x < position.x + width)
		&& (position.y < mousePos->y && mousePos->y < position.y + height))
	{
		state = ButtonState::HOVER;
		drawColor = LIGHTGRAY;
	}
	else
	{
		state = ButtonState::IDLE;
		drawColor = WHITE;
	}

	if (state == ButtonState::HOVER)
	{
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			state = ButtonState::CLICK;
			drawColor = DARKGRAY;

			ButtonCliqued();

		}
	}

}

float fontSize = 10;
void Button::Draw()
{
	if (!isActive) return;
	if (sprite.width >= 0)
	{
		DrawTexture(sprite, position.x , position.y, drawColor);

	}
	else
	{
		DrawRectangle(position.x, position.y, width, height, drawColor);
	}
	/*
	if (textInButton != "")
	{
		DrawText(textInButton.c_str(), position.x+ width/2 - textInButton.length(), position.y + height/2 , (width + height) /20, WHITE);
	}*/

}


void Button::CliquedSendFunction()
{
	if (functPrt != nullptr)
	{
		(*functPrt)();
	}
}

void Button::CliquedSendFunctionWithInt()
{
	call();
	if (functPrtInt != nullptr)
	{
		if (value != NULL)
		{
			(*functPrtInt)(value);
		}
	}
}


void Button::AddFunctionToTrigger(std::function<void()> func)
{
	functionsToTrigger.push_back(func);
}

void Button::call()
{
	for (auto i = functionsToTrigger.begin(); i != functionsToTrigger.end(); ++i)
	{
		(*i)();
	}
}