#include "Pong.h"

using namespace sf;

//ADD GET AND SET
float playerSpeed = 200;
float ballSpeedX = 100;
float ballSpeedY = 0;
bool player1PowerUpActive = false;
bool player2PowerUpActive = false;

Player player1(200.0f, 1, Vector2f(50,300), Keyboard::Key::Up, Keyboard::Key::Down);
Player player2(200.0f, 2, Vector2f(750, 300), Keyboard::Key::W, Keyboard::Key::S);

//PowerUps powerup;

RenderWindow* window;
Keyboard keys;
Clock sfClock;
float deltaTime;

int middlePos[32];

int punishment = 1;
int punishmentLevel = 1;

std::map<int, Color> punishments;


Pong::Pong() {
    ball = CircleShape(10);
    ball.setFillColor(Color(200, 200, 200));
    ball.setPosition(400, 300);

    //line in the middle
    middle = RectangleShape(Vector2f(10, 10));
    middle.setFillColor(Color(200, 200, 200));

    int yPos = 0;
    for (int i = 0; i < 32; i += 1) {
        middlePos[i] = yPos;
        yPos += 20;
    }
}
Pong::Pong(RenderWindow* mainWindow, int serial) {
    window = mainWindow;
    serial_fd = serial;
    ball = CircleShape(10);
    ball.setFillColor(Color(200, 200, 200));
    ball.setPosition(400, 300);

    //line in the middle
    middle = RectangleShape(Vector2f(10, 10));
    middle.setFillColor(Color(200, 200, 200));

    int yPos = 0;
    for (int i = 0; i < 32; i += 1) {
        middlePos[i] = yPos;
        yPos += 20;
    }
    punishments[0] = Color::Black;
    punishments[1] = Color::Red;
    punishments[2] = Color::Blue;
    punishments[3] = Color::Yellow;

}

void Pong::setPunishmentColor(Player* player) {
    punishment = (rand() % 3) + 1;
    player->punishmentRect->setFillColor(punishments[punishment]);
    std::cout << "set color" << punishment << std::endl;
}

void Pong::movePlayer(Player* player, Keyboard::Key upKey, Keyboard::Key downKey)
{
    //move player within the window
    playerShape = player->playerObject;
    playerXPos = playerShape.getPosition().x;
    playerYPos = playerShape.getPosition().y;
    if (keys.isKeyPressed(downKey) && playerYPos < (window->getSize().y - playerShape.getSize().y)) {
        playerYPos += (playerSpeed * deltaTime);
    }
    if (keys.isKeyPressed(upKey) && playerYPos > 0) {
        playerYPos -= (playerSpeed * deltaTime);
    }
    player->playerObject.setPosition(playerXPos, playerYPos);
    player = nullptr;
    delete player;
}

void Pong::moveBall(CircleShape* ball, Player player1, Player player2)
{
    //PREDECLARE VARIABLES TO SAVE MEMORY
    ballPosition = ball->getPosition();
    player1Pos = player1.playerObject.getPosition();
    player2Pos = player2.playerObject.getPosition();
    player1Bounds = player1.playerObject.getGlobalBounds();
    player2Bounds = player2.playerObject.getGlobalBounds();
    speedModifier = Vector2f(1, 1);
    ballRadius = ball->getRadius();
    //if it hits the bottom/top wall
    if (ball->getPosition().y >= ((window->getSize().y - ball->getRadius() * 2)-5) || ballPosition.y <= 5)
    {
        ballSpeedY *= -1;
    }

    //if it hits behind a player count that against the player it missed
    if ((ballPosition.x >= window->getSize().x - ball->getRadius() * 2 -5))
    {
        speedModifier = ballHitsBehindPlayer(&player2);
    }
    else if (ballPosition.x <= 5) {
        speedModifier =  ballHitsBehindPlayer(&player1);
    }
    if ((player1Bounds.contains(ballPosition.x, ballPosition.y - (ballRadius)) || player1Bounds.contains(ballPosition.x, ballPosition.y + ballRadius)) && ballSpeedX < 0) {
        speedModifier = deflectBall(*ball, player1.playerObject);
        setPunishmentColor(&player1);
    }
    if ((player2Bounds.contains(ballPosition.x + ballRadius, ballPosition.y - (ballRadius)) || player2Bounds.contains(ballPosition.x + ballRadius, ballPosition.y + ballRadius)) && ballSpeedX > 0) {
        speedModifier = deflectBall(*ball, player2.playerObject);
        setPunishmentColor(&player2);
    }
    ballSpeedX *= speedModifier.x;
    ballSpeedY *= speedModifier.y;
    ball->move(ballSpeedX * deltaTime, ballSpeedY * deltaTime);
    ball = nullptr;
    delete ball;
}

Vector2f Pong::ballHitsBehindPlayer(Player* player) {
        //PAIN INFORMATION GOES HERE
        //perhaps ball changes color to determine pain stimulus
        // or homage to orig pain station
        //Player missed
        player->misses += 1;
        setPunishmentColor(player);
         //send message
         // 
           //  //3 int's, player + punishment + punishment level
           //const char* message = player->playerID + punishment + 2 + "\n";
           // ssize_t bytes_written = write(serial_fd, message, strlen(message));
        
           // if (bytes_written < 0) {
           //     std::cerr << "error writing to serial port" << std::endl;
           // } else {
           //     std::cout << "successfully wrote " << bytes_written << " bytes to serial port" << std::endl;
           // }
        player = nullptr;
        delete player;
        return Vector2f(-1, 1);
}


Vector2f Pong::deflectBall(CircleShape ball, RectangleShape player) {
    //DECLARE EXTERNAL FOR MEMORY
    ballPosition = ball.getPosition();
    playerPos = player.getPosition();
    ballRadius = ball.getRadius();
    ballSpeedY = 10;
    if (ballPosition.y > (player.getPosition().y - player.getSize().y / 3)) {
        //if ball hits top third
        ballSpeedY *= 1.5;
    }
    if (ballPosition.y < (playerPos.y - ((player.getSize().y / 3) * 2))) {
        //if ball hits bottom third
        ballSpeedY *= .5;
    }
    return Vector2f(-1, ballSpeedY);
}

int Pong::Play()
{
    std::cout << "Play";
    // run the program as long as the window is open
    sfClock.restart();
    while (window->isOpen())
    {
        deltaTime = sfClock.restart().asSeconds();
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window->pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == Event::Closed)
                window->close();
        }

        // clear the window with black color
        window->clear(Color::Black);

        //update the player position
        movePlayer(&player1, Keyboard::Up, Keyboard::Down);
        movePlayer(&player2, Keyboard::W, Keyboard::S);

        //update the circle position
        moveBall(&ball, player1, player2);
          

        //render objects
        window->draw(ball);
        window->draw(player1.playerObject);
        window->draw(player2.playerObject);
        window->draw(*player1.punishmentRect);
        window->draw(*player2.punishmentRect);
        for (int i = 0; i < 32; i++)
        {
            middle.setPosition(400, middlePos[i]);
            window->draw(middle);
        }
        
        // end the current frame
        window->display();
    }
    return 0;
}

