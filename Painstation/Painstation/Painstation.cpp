// Painstation.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#define SFML_STATIC
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
using namespace sf;
#include "Pong.h"
#include "Button.h"
//#include <fcntl.h>
//#include <termios.h>
//#include <unistd.h>
//#include <string.h>

RenderWindow* window;
Button* pongButton;
int serial_fd;
const char* serial_port_path;
Font font;
Text disclaimer;

//
//int serial() {
//
//    //make the serial path
//    serial_port_path = "/dev/ttyACM0";
//    //open the path for the serial coms
//    serial_fd = open(serial_port_path, O_RDWR);
//
//    if (serial_fd < 0) {
//        std::cerr << "Error opening serial port" << std::endl;
//        return -1;
//    }
//
//    struct termios tty;
//    memset(&tty, 0, sizeof(tty));
//    if (tcgetattr(serial_fd, &tty) != 0) {
//        std::cerr << "Error getting serial port attributes" << std::endl;
//        close(serial_fd);
//        return -1;
//    }
//
//    cfsetospeed(&tty, B9600);
//    cfsetispeed(&tty, B9600);
//
//    tty.c_cflag |= (CLOCAL | CREAD);
//    tty.c_cflag &= ~PARENB;
//    tty.c_cflag &= ~CSTOPB;
//    tty.c_cflag &= ~CSIZE;
//    tty.c_cflag |= CS8;
//
//    if (tcsetattr(serial_fd, TCSANOW, &tty) != 0) {
//        std::cerr << "Error setting serial port attributes" << std::endl;
//        close(serial_fd);
//        return -1;
//    }
//
//    //send message
//    const char* message = "Hello, Serial!\n";
//    ssize_t bytes_written = write(serial_fd, message, strlen(message));
//
//    if (bytes_written < 0) {
//        std::cerr << "Error writing to serial port" << std::endl;
//    }
//    else {
//        std::cout << "Successfully wrote " << bytes_written << " bytes to serial port" << std::endl;
//    }
//
//    return 0;
//}


int main()
{
    //make the window
    window = new RenderWindow(VideoMode(800, 600), "My window");

    //disclaimer
    font.loadFromFile("..\\Font\\Roboto-VariableFont_wdth,wght.ttf");
    disclaimer.setFont(font);
    disclaimer.setPosition(300, 200);
    disclaimer.setCharacterSize(30);
    disclaimer.setString("DISCLAIMER NOT WRITTEN YET,\nBY PRESSING PLAY YOU AGREE\nTO THESE TERMS AND CONDITIONS.");

    pongButton = new Button(Vector2f(100, 100), Vector2f(100, 250), "Pong", 1);
    pongButton->active = true;

    //serial();
    // run the program as long as the window is open
    while (window->isOpen())
    {
        Event e;
        while (window->pollEvent(e))
        {
            if (e.type == Event::Closed)
                window->close();
        }
        if (!Mouse::isButtonPressed(Mouse::Left) && !Mouse::isButtonPressed(Mouse::Right))
            pongButton->released = true;

        if (pongButton->clicked)
        {
            pongButton->active = false;
            std::cout << "clickedLeft";
            Pong p(window, serial_fd);
            p.Play();
        }
     
        if (pongButton->active) {
            pongButton->update(*window);
            window->draw(disclaimer);
        }

        // end the current frame
        window->display();
    }
    //close(serial_fd);
    return 0;
}


