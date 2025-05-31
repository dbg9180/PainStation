#pragma once
#pragma once
#include <iostream>
#define SFML_STATIC
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
using namespace sf;

class Button
{
	public:
	Button(Vector2f, Vector2f, std::string, int);
	RectangleShape buttonSprite;
	bool clicked = false;
	bool active = false;
	Text buttonText;
	Vector2f textPosition;
	int destination;
	void update(RenderWindow&);
	bool released;

};

