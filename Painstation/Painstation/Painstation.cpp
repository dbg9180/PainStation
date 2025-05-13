// Painstation.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#define SFML_STATIC
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
using namespace sf;
#include "Pong.h"

int main()
{
    Pong* p = new Pong();
    p->Play();
    return 0;
}


