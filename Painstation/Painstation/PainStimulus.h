#pragma once
#include <iostream>
#define SFML_STATIC
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Player.h"
using namespace sf;

class PainStimulus
{
	public:
		PainStimulus(int, Player*);
		RectangleShape painObject;
		Player* playerToPain;
		int painType; //1 = , 2= , 3=

	private:
};

