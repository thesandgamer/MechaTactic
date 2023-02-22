#pragma once
#include <raylib.h>
#include <string>
#include <iostream>
#include <functional>


typedef std::function<void()> MemberCallback;//Créer un type pointeur fonction void, créer le type du lambda

enum class ButtonState
{
    IDLE, HOVER, CLICK
};

class Button
{
public:
    Button();
    Button(Vector2 pos, Texture2D spriteP, float widthP, float heightP);
    Button(Vector2 pos, float widthP, float heightP);
    ~Button();

    void ButtonCliqued();
    void ButtonHovered();

    void Update();
    void Draw();

    Vector2* mousePos;

    void CliquedSendFunction();
    void CliquedSendFunctionWithInt();

    void (*functPrt)();
    void (*functPrtInt)(int);

    int value;

    std::string textInButton;

    void setCallback(MemberCallback newCallback) { callback = newCallback; }//Set l'instance
    void call();//Appel

    bool isActive = true;

private:
    ButtonState state;


    Vector2 position;
    float width;
    float height;
    Texture2D sprite;

    Color drawColor ;


    MemberCallback callback; //instance de pointeur de fonction

};

