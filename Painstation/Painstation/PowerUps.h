#pragma once
#define SFML_STATIC
#include <SFML/Graphics.hpp>
#include <iostream>
//#include "Player.h"
using namespace sf;

//Use cases: 
		//gives other player pain
		//speeds up other player
		//gives immunity to next pain

int immunityPoint;
float otherPlayerSpeed;

//[event_scource(native)]
class PowerUps
{
	public:
		//default constructor
		PowerUps();
		//base powerup
		PowerUps(Color);
		//speeds up other player
		PowerUps(Color, float);
		//gives immunity to next pain
		PowerUps(Color, int);
		__event void HitPlayer();
		RectangleShape powerUpObject;
};

