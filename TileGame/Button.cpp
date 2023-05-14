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

void Button::ButtonIdle()
{
	state = ButtonState::IDLE;
	drawColor = WHITE;
}

void Button::ButtonCliqued()
{
	TraceLog(LOG_INFO, " Button cliqued");
	drawColor = GRAY;

	CliquedSendFunction();
	CliquedSendFunctionWithInt();

	state = ButtonState::CLICK;
}

void Button::ButtonHovered()
{
	if (!lever)
	{
		state = ButtonState::HOVER;
		drawColor = LIGHTGRAY;
	}
	if (lever)
	{
		if (state != ButtonState::CLICK)
		{
			state = ButtonState::HOVER;
			drawColor = LIGHTGRAY;
		}
	}
	
}

void Button::Update()
{
	if (!isActive) return;
	mousePos = &GetMousePosition();

	ButtonState oldState = ButtonState::IDLE; 
	if (state != ButtonState::HOVER)
	{
		oldState = state;
	}

	//Check Si la souris est en hover
	if ((position.x < mousePos->x && mousePos->x < position.x + width)
		&& (position.y < mousePos->y && mousePos->y < position.y + height))	//If hover
	{
		ButtonHovered();
		if (lever)
		{
			if (state == ButtonState::CLICK)//Si on hover le bouton déjà cliqué
			{
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
				{
					ButtonCliqued();
					ButtonIdle();
					
				}
			}
		}
	}
	else
	{
		if (!lever)	//Si le bouton n'est pas un levier
		{
			ButtonIdle();
		}
		else
		{
			//Retourne à l'état avant d'être hover
			if (oldState == ButtonState::CLICK)
			{
				drawColor = GRAY;
				state = ButtonState::CLICK;
			}
			if (oldState == ButtonState::IDLE)
			{
				ButtonIdle();
			}

		}

		
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
	if (sprite.width >= 0)	//Si il possède un sprite
	{
		DrawTexture(sprite, position.x , position.y, drawColor);

	}
	else
	{
		DrawRectangle(position.x, position.y, width, height, drawColor);
	}

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