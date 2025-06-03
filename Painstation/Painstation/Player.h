#pragma once
#include <iostream>
#define SFML_STATIC
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
using namespace sf;
#include "PowerUps.h"




class Player
{

public:
	Player(float, int, Vector2f, Keyboard::Key, Keyboard::Key);
	void PowerUpGained();
	void hookEvent(PowerUps*);
	void unhookEvent(PowerUps*);
	RectangleShape playerObject;
	int misses;
	int immunityPoints;
	int playerID;
	RectangleShape* punishmentRect;
private:
	float speed;
	Keyboard::Key upKey;
	Keyboard::Key downKey;
};
	

