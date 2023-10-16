#pragma once
#include <raylib.h>
#include <string>
#include <iostream>
#include <functional>


//++ToDo: refacto cette classe
//++ToDo; faire en sorte que le bouton peut être en type levier(reste appuyé(en tout cas visuellement))

//++ToDo: refacto pour que la façon levier fonctionne mieux avec un couleur reste activé

typedef std::function<void()> FuncPointer;//Créer un type pointeur fonction void, créer le type du lambda

//++ToDo: créer un pointeur de fonction pour quand hover

enum class ButtonState
{
    IDLE, HOVER, PRESSED,CLICK, INACTIVE
};

class Button
{
public:
    Button();
    Button(Vector2 pos, Texture2D spriteP);
    Button(Vector2 pos, float widthP, float heightP);
    ~Button();

    void SetSprite(Texture2D sprite);

    void ButtonIdle();
    void ButtonCliqued();
    void ButtonHovered();
    void ButtonPressed();

    void UnPressButton();

    void DeactivteButton();
    void ReactivateButton();

    void Update();
    void Draw();
    void DrawAt(Vector2 pos);


    Vector2 mousePos;

    void CliquedSendFunction();
    void CliquedSendFunctionWithInt();

    void HoverSendFunction();

    void (*functPrt)();
    void (*functPrtInt)(int);

    int value;

    std::string textInButton;

    void AddFunctionToTrigger(std::function<void()> func);//Set l'instance
    void AddHoverFunction(std::function<void()> func);

    void call();//Appel
    void callHover();

    bool isActive = true;

    bool lever{ false };


private:
    ButtonState state;

    Vector2 position;

    Texture2D spriteIdle;   //Pourrait être un pointeur avec un ressource manager
    Texture2D spriteCliked;
    Texture2D spriteHover;
    Texture2D spritePressed;

    float width;
    float height;

    Color drawColor ;

    Color idleColor {WHITE};
    Color hoverColor{ DARKGRAY };
    Color pressedColor {100,100,100,255};
    Color clickedColor {BLACK};
    Color deactivateColor { 255,2,20,255 };

    bool isPressed{ false };



    std::vector<std::function<void()>> functionsToTrigger{}; //instance de pointeur de fonction
    std::vector<std::function<void()>> hoverFunctionToTrigger{};

};

