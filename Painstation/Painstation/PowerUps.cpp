#include "PowerUps.h"
#include <stdio.h>

PowerUps::PowerUps(Color fillColor)
{
	powerUpObject.setFillColor(fillColor);
	powerUpObject.setPosition(20,20);
	powerUpObject.setSize(Vector2f(10, 10));
}

PowerUps::PowerUps(Color fillColor, float oppositePlayerSpeed)
{
	//speeds up other player
	powerUpObject.setFillColor(fillColor);
	otherPlayerSpeed = oppositePlayerSpeed;

	powerUpObject.setPosition(20, 20);
	powerUpObject.setSize(Vector2f(10, 10));
}

PowerUps::PowerUps(Color fillColor, int immunityPoints)
{
	//gives immunity to next pain
	powerUpObject.setFillColor(fillColor);
	immunityPoint = immunityPoints;

	powerUpObject.setPosition(20, 20);
	powerUpObject.setSize(Vector2f(10, 10));
}



