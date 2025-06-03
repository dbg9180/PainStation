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
	//default constructor
	Pong();
	Pong(RenderWindow*, int);
	void setPunishmentColor(Player*);
	Vector2f deflectOffPlayer(float ballPositionY, float playerPosY, float playerSizeY);
	int Play();

	Vector2f velocity;
	Vector2f ballPosition;
	Vector2f playerPos;
	float ballRadius;
	Vector2f player1Pos;
	Vector2f player2Pos;
	FloatRect player1Bounds;
	FloatRect player2Bounds;
	Vector2f speedModifier;
	RectangleShape playerShape;
	float playerXPos;
	float playerYPos;
	CircleShape ball;
	RectangleShape middle;
private:
	void movePlayer(Player*, Keyboard::Key, Keyboard::Key);
	void moveBall(CircleShape*, Player, Player);
	Vector2f deflectBall(CircleShape, RectangleShape);
	Vector2f ballHitsBehindPlayer(Player*);
	int serial_fd;
	
};

