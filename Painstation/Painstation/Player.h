#pragma once
#include <iostream>
#define SFML_STATIC
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
using namespace sf;
#include "PowerUps.h"
using namespace sf;

float speed;
Keyboard::Key upKey;
Keyboard::Key downKey;

class Player
{

public:
	Player(float, Vector2f, Keyboard::Key, Keyboard::Key);
	void PowerUpGained();
	void hookEvent(PowerUps*);
	void unhookEvent(PowerUps*);
	RectangleShape playerObject;
	int score;
	int immunityPoints;
};
	

