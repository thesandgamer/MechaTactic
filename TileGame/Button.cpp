#include "Button.h"
Button::Button()
{
}

Button::Button(Vector2 pos, Texture2D spriteP):position(pos), spriteIdle(spriteP), width(spriteP.width), height(spriteP.height), 
state(ButtonState::IDLE), functPrt(nullptr), functPrtInt(nullptr)
{
	drawColor = idleColor;
	value = -1;
}

Button::Button(Vector2 pos, float widthP, float heightP) : position(pos), width(widthP), height(heightP), 
state(ButtonState::IDLE), functPrt(nullptr), functPrtInt(nullptr)
{
	drawColor = idleColor;
	value = -1;

}

Button::~Button()
{

}

void Button::ButtonIdle()
{
	state = ButtonState::IDLE;
	drawColor = idleColor;
}

void Button::ButtonCliqued()
{
	if (lever) ButtonPressed();
	TraceLog(LOG_INFO, " Button cliqued");

	state = ButtonState::CLICK;

	drawColor = clickedColor;

	//Activate function
	CliquedSendFunction();
	CliquedSendFunctionWithInt();

}

void Button::ButtonHovered()
{
	state = ButtonState::HOVER;
	drawColor = hoverColor;
	HoverSendFunction();
}

void Button::ButtonPressed()
{
	if (!lever)
	{
		state = ButtonState::PRESSED;
		drawColor = pressedColor;
		isPressed = true;
	}
	else//Si c'est un levier
	{
		if (isPressed)
		{
			ButtonIdle();
			isPressed = false;

		}
		else
		{
			isPressed = true;
			drawColor = pressedColor;

		}
	}

}

void Button::UnPressButton()
{
	isPressed = false;
	ButtonIdle();
}

void Button::Update()
{
	if (!isActive) return;
	mousePos = GetMousePosition();

	//ButtonState oldState = state;

	//Check Si la souris est en hover
	if ((position.x < mousePos.x && mousePos.x < position.x + width)
		&& (position.y < mousePos.y && mousePos.y < position.y + height))	//If hover button
	{
		ButtonHovered();
	}
	else
	{
		if (isPressed) {
			drawColor = pressedColor;
			state = ButtonState::PRESSED;
		}
		else ButtonIdle();
	}

	if (state == ButtonState::HOVER)
	{
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			ButtonCliqued();

		}
	}

}

float fontSize = 10;
void Button::Draw()
{
	if (!isActive) return;
	if (spriteIdle.width >= 0)	//Si il possède un sprite
	{
		DrawTexture(spriteIdle, position.x , position.y, drawColor);

	}
	else
	{
		DrawRectangle(position.x, position.y, width, height, drawColor);
	}

}

void Button::DrawAt(Vector2 pos)
{
	Draw();
	position = pos;
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

void Button::HoverSendFunction()
{
	callHover();
}


void Button::AddFunctionToTrigger(std::function<void()> func)
{
	functionsToTrigger.push_back(func);
}

void Button::AddHoverFunction(std::function<void()> func)
{
	hoverFunctionToTrigger.push_back(func);
}

void Button::call()
{
	for (auto i = functionsToTrigger.begin(); i != functionsToTrigger.end(); ++i)
	{
		(*i)();
	}
}

void Button::callHover()
{
	for (auto i = hoverFunctionToTrigger.begin(); i != hoverFunctionToTrigger.end(); ++i)
	{
		(*i)();
	}
}
