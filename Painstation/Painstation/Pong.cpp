#include "Pong.h"
//#include "serialThirdParty/include/serial/serial.h"
//#include "thread"

using namespace sf;

//PUT ARDUINO PORT IN FIRST VARAIBLE, THE STRING
//serial::Serial mySerial("C:/Users/Aydee/Desktop/serial test.txt", 19200, serial::Timeout::simpleTimeout(3000));
//serial::Serial imHere;

float playerSpeed = 200;
float ballSpeedX = 100;
float ballSpeedY = 0;

Player player1(200.0f, Vector2f(50,300), Keyboard::Key::Up, Keyboard::Key::Down);
Player player2(200.0f, Vector2f(750, 300), Keyboard::Key::W, Keyboard::Key::S);

PowerUps powerup(Color(255, 87, 51));

RenderWindow* window;
Keyboard keys;
Clock sfClock;
float deltaTime;

void Pong::movePlayer(Player* player, Keyboard::Key upKey, Keyboard::Key downKey)
{
    //move player within the window
    RectangleShape playerShape = player->playerObject;
    float playerXPos = playerShape.getPosition().x;
    float playerYPos = playerShape.getPosition().y;
    if (keys.isKeyPressed(downKey) && playerYPos < (window->getSize().y - playerShape.getSize().y)) {
        playerYPos += (playerSpeed * deltaTime);
    }
    if (keys.isKeyPressed(upKey) && playerYPos > 0) {
        playerYPos -= (playerSpeed * deltaTime);
    }
    player->playerObject.setPosition(playerXPos, playerYPos);

}
//void sendSerial() {
//    //confirm serial is open and ready
//    if (mySerial.isOpen()) {
//        std::cout << "Port opend successfully" << std::endl;
//    }
//    else {
//        //exit this function if it failed to open
//        std::cout << "Port failed to open" << std::endl;
//        exit(1);
//    }
//    mySerial.flushOutput();
//
//    //send a message 3 times to make sure Arduino recieves something
//    for (int i = 0; i < 3; i++) {
//        size_t bytesWritten = mySerial.write("hi");
//        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
//    }
//    mySerial.flushInput();
//}

void Pong::moveBall(CircleShape* ball, Player player1, Player player2)
{
    Vector2f ballPosition = ball->getPosition();
    Vector2f player1Pos = player1.playerObject.getPosition();
    Vector2f player2Pos = player2.playerObject.getPosition();
    FloatRect player1Bounds = player1.playerObject.getGlobalBounds();
    FloatRect player2Bounds = player2.playerObject.getGlobalBounds();
    Vector2f speedModifier(1, 1);
    float ballRadius = ball->getRadius();
    //if it hits the bottom/top wall
    if (ball->getPosition().y >= (window->getSize().y - ball->getRadius() * 2) || ballPosition.y <= 0)
    {
        ballSpeedY *= -1;
    }
    //if it hits behind a player count that against the player it missed
    if ((ballPosition.x >= window->getSize().x - ball->getRadius() * 2))
    {
        //PAIN INFORMATION GOES HERE
        //Player 2 missed
        player2.score += 1;
        if (player2.score >= 1) {
            //spawn a powerup
            window->draw(powerup.powerUpObject);
            std::cout << "power!" << std::endl;
        }
        ballSpeedX *= -1;
    }
    else if (ballPosition.x <= 0){
        //PAIN INFORMATION GOES HERE
        //Player 1 missed
        player1.score += 1;
        if (player1.score >= 1) {
            //spawn a powerup
        }
        ballSpeedX *= -1;
    }
    if (player1Bounds.contains(ballPosition.x, ballPosition.y - (ballRadius)) || player1Bounds.contains(ballPosition.x, ballPosition.y + ballRadius)) {
        std::cout << "hit player 1";
        speedModifier = deflectBall(*ball, player1.playerObject);
    }
    if (player2Bounds.contains(ballPosition.x + ballRadius, ballPosition.y - (ballRadius)) || player2Bounds.contains(ballPosition.x + ballRadius, ballPosition.y + ballRadius)) {
        std::cout << "hit player 2";
        speedModifier = deflectBall(*ball, player2.playerObject);
    }
    ballSpeedX *= speedModifier.x;
    ballSpeedY *= speedModifier.y;
    ball->move(ballSpeedX * deltaTime, ballSpeedY * deltaTime);
}



Vector2f Pong::deflectBall(CircleShape ball, RectangleShape player) {
    Vector2f velocity;
    Vector2f ballPosition = ball.getPosition();
    Vector2f playerPos = player.getPosition();
    float ballRadius = ball.getRadius();
    ballSpeedY = 10;
    if (ballSpeedX < 0) {
        if (ballPosition.y > (playerPos.y - player.getSize().y / 3)) {
            //if ball hits top third
            ballSpeedY *= 1.5;
           }
        if (ballPosition.y < (playerPos.y - ((player.getSize().y / 3) * 2))) {
            //if ball hits bottom third
            ballSpeedY *= .5;
        }
            velocity = Vector2f(-1, ballSpeedY);
    }
    else
    {
        if (ballPosition.y > (playerPos.y - player.getSize().y / 3)) {
            //if ball hits top third
            ballSpeedY *= 1.5;
        }
        if (ballPosition.y < (playerPos.y - ((player.getSize().y / 3) * 2))) {
            //if ball hits bottom third
            ballSpeedY *= 5;
        }
            velocity = Vector2f(-1, ballSpeedY);

    }
    return velocity;
}

int Pong::Play()
{
    //make the window
    window = new RenderWindow(VideoMode(800, 600), "My window");

    //make all the necessary starting objects
    //ball
    CircleShape ball(10);
    ball.setFillColor(Color(200, 200, 200));
    ball.setPosition(400, 300);

    //line in the middle
    RectangleShape middle(Vector2f(10, 10));
    middle.setFillColor(Color(200, 200, 200));

    std::cout << "Play";
    // run the program as long as the window is open
    while (window->isOpen())
    {
        player1.hookEvent(&powerup);

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

        window->draw(ball);
        window->draw(player1.playerObject);
        window->draw(player2.playerObject);
        for (float i = 0; i < 600; i += 20) {
            middle.setPosition(400, i);
            window->draw(middle);
        }
        // end the current frame
        window->display();
    }
    player1.unhookEvent(&powerup);
    return 0;
}

