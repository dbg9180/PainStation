// Painstation.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#define SFML_STATIC
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
using namespace sf;

int circleXPos = 400;
int circleYPos = 300;

int player1XPos = 50;
int player1YPos = 300;
int player2XPos = 750;
int player2YPos = 300;

int main()
{
    //make the window
    RenderWindow window(VideoMode(800, 600), "My window");

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == Event::Closed)
                window.close();
        }

        // clear the window with black color
        window.clear(Color::Black);

        // draw everything here...
        // window.draw(...);
        CircleShape circle(10);
        circle.setFillColor(Color(200, 200, 200));
        circle.setPosition(circleXPos, circleYPos);

        RectangleShape player1(Vector2f(10,30));
        player1.setFillColor(Color(200, 200, 200));
        player1.setPosition(player1XPos, player1YPos);

        RectangleShape player2(Vector2f(10, 30));
        player2.setFillColor(Color(200, 200, 200));
        player2.setPosition(player2XPos, player2YPos);
       
        //line in the middle
        RectangleShape middle(Vector2f(10, 10));
        middle.setFillColor(Color(200, 200, 200));
        for (int i = 0; i < 600; i += 20) {
            middle.setPosition(400, i);
            window.draw(middle);
        }


        //update the player position
        movePlayer(player1, 1);
        movePlayer(player2, 2);
        //update the circle position

        window.draw(circle);
        window.draw(player1);
        window.draw(player2);


        // end the current frame
        window.display();
    }

    return 0;
}


void movePlayer(RectangleShape player, int playerNumber) 
{
    //determine which keys to use
    if (playerNumber == 1) {

        return;
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
