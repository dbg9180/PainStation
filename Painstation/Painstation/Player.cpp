#include "Player.h"

Player::Player(float speeds, Vector2f position, Keyboard::Key keyUp, Keyboard::Key keyDown) {
	playerObject.setSize(Vector2f(10, 30));
	playerObject.setFillColor(Color(255, 255, 255));
	playerObject.setPosition(position);
	speed = speeds;
	upKey = keyUp;
	score = 0;
	immunityPoints = 0;
}

void Player::PowerUpGained()
{
	printf_s("MyHandler1 was called");
}

void Player::hookEvent(PowerUps* powerUp)
{
	__hook(&PowerUps::HitPlayer, powerUp, &Player::PowerUpGained);
}

void Player::unhookEvent(PowerUps* powerUp) {
	__unhook(&PowerUps::HitPlayer, powerUp, &Player::PowerUpGained);
}