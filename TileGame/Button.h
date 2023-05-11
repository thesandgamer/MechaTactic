#pragma once
#include <raylib.h>
#include <string>
#include <iostream>
#include <functional>


//++ToDo: refacto cette classe
//++ToDo; faire en sorte que le bouton peut être en type levier(reste appuyé(en tout cas visuellement))


typedef std::function<void()> FuncPointer;//Créer un type pointeur fonction void, créer le type du lambda

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

    void AddFunctionToTrigger(std::function<void()> func);//Set l'instance
    void call();//Appel

    bool isActive = true;

private:
    ButtonState state;


    Vector2 position;
    float width;
    float height;
    Texture2D sprite;   //Pourrait être un pointeur avec un ressource manager

    Color drawColor ;


    std::vector<std::function<void()>> functionsToTrigger; //instance de pointeur de fonction

};

