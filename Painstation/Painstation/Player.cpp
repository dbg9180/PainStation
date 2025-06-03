#include "Player.h"

Player::Player(float speeds, int playerID, Vector2f position, Keyboard::Key keyUp, Keyboard::Key keyDown) {
	playerObject.setSize(Vector2f(10, 30));
	playerObject.setFillColor(Color(255, 255, 255));
	playerObject.setPosition(position);
	speed = speeds;
	upKey = keyUp;
	this->playerID = playerID;
	misses = 0;
	immunityPoints = 0;
	punishmentRect = new RectangleShape(Vector2f(10, 600));
	if (position.x > 400) {
		punishmentRect->setPosition(position.x + 40, 0);
	}
	else {
		punishmentRect->setPosition(position.x - 50, 0);
	}
	punishmentRect->setFillColor(Color::Black);
}

void Player::PowerUpGained()
{
	std::cout << "hi" << std::endl;
}

void Player::hookEvent(PowerUps* powerUp)
{
	__hook(&PowerUps::HitPlayer, powerUp, &Player::PowerUpGained);
	powerUp = nullptr;
	delete powerUp;
}

void Player::unhookEvent(PowerUps* powerUp) {
	__unhook(&PowerUps::HitPlayer, powerUp, &Player::PowerUpGained);
	powerUp = nullptr;
	delete powerUp;
}