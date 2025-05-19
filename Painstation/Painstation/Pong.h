#pragma once
#include "Player.h"
#include <iostream>
#define SFML_STATIC
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
using namespace sf;
class Pong
{
public:
	int Play();

private:
	void movePlayer(Player*, Keyboard::Key, Keyboard::Key);
	void moveBall(CircleShape*, Player, Player);
	Vector2f deflectBall(CircleShape, RectangleShape);
};

