#pragma once
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
	void movePlayer(RectangleShape*, Keyboard::Key, Keyboard::Key);
	void moveBall(CircleShape*, RectangleShape, RectangleShape);
	Vector2f deflectBall(CircleShape, RectangleShape);
};

