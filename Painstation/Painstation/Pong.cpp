#include "Pong.h"
#include <iostream>
#define SFML_STATIC
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
using namespace sf;

float playerSpeed = 200;
float ballSpeedX = 100;
float ballSpeedY = 0;

RenderWindow* window;
Keyboard keys;
Clock sfClock;
float deltaTime;


void Pong::movePlayer(RectangleShape* player, Keyboard::Key upKey, Keyboard::Key downKey)
{
    //move player within the window
    float playerXPos = player->getPosition().x;
    float playerYPos = player->getPosition().y;
    if (keys.isKeyPressed(downKey) && playerYPos < (window->getSize().y-player->getSize().y)) {
        playerYPos += (playerSpeed * deltaTime);
    }
    if (keys.isKeyPressed(upKey) && playerYPos >0 ) {
        playerYPos -= (playerSpeed * deltaTime);
    }
    player->setPosition(playerXPos, playerYPos);
    
}

void Pong::moveBall(CircleShape* ball, RectangleShape player1, RectangleShape player2)
{
    Vector2f ballPosition = ball->getPosition();
    Vector2f player1Pos = player1.getPosition();
    Vector2f player2Pos = player2.getPosition();
    Vector2f speedModifier(1, 1);
    float ballRadius = ball->getRadius();
    //if it hits the bottom/top wall
    if (ball->getPosition().y >= (window->getSize().y - ball->getRadius()*2) || ballPosition.y <= 0)
    {
        ballSpeedY *= -1;
    }
    //if it hits behind a player end the game
    if ((ballPosition.x >= window->getSize().x - ball->getRadius() * 2) || ballPosition.x <= 0)
    {
        //PAIN INFORMATION GOES HERE
        playerSpeed = 0;
        ballSpeedX = 0;
        ballSpeedY = 0;
    }
    if (player1.getGlobalBounds().contains(ballPosition.x, ballPosition.y - (ballRadius)) || player1.getGlobalBounds().contains(ballPosition.x, ballPosition.y + ballRadius)) {
        std::cout << "hit player";
        speedModifier = deflectBall(*ball, player1);
    }
    if (player2.getGlobalBounds().contains(ballPosition.x + ballRadius, ballPosition.y - (ballRadius)) || player2.getGlobalBounds().contains(ballPosition.x + ballRadius, ballPosition.y + ballRadius)) {
        std::cout << "hit player";
        speedModifier = deflectBall(*ball, player2);
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
    if (ballSpeedX < 0) {
            std::cout << "hit player 1";
            velocity = Vector2f(-1, 0);
    }
    else
    {
            std::cout << "hit player 2";
            velocity = Vector2f(-1, 0);

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

    //players
    RectangleShape player1(Vector2f(10, 30));
    player1.setFillColor(Color(200, 200, 200));
    player1.setPosition(50, 300);

    RectangleShape player2(Vector2f(10, 30));
    player2.setFillColor(Color(200, 200, 200));
    player2.setPosition(750, 300);

    //line in the middle
    RectangleShape middle(Vector2f(10, 10));
    middle.setFillColor(Color(200, 200, 200));


    std::cout << "Play";
    // run the program as long as the window is open
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

        // draw everything here...
        // window.draw(...);
        

        //update the player position
        movePlayer(&player1, Keyboard::Up, Keyboard::Down);
        movePlayer(&player2, Keyboard::W, Keyboard::S);

        //update the circle position
        moveBall(&ball, player1, player2);

        window->draw(ball);
        window->draw(player1);
        window->draw(player2);
        for (float i = 0; i < 600; i += 20) {
            middle.setPosition(400, i);
            window->draw(middle);
        }
        // end the current frame
        window->display();
    }

    return 0;
}

