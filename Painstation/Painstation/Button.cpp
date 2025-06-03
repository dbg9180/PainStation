#include "Button.h"
Font font;


Button::Button(Vector2f size, Vector2f position, std::string text, int destination) {
	buttonSprite = RectangleShape(size);
    buttonSprite.setFillColor(Color::White);
	buttonSprite.setPosition(position);
	textPosition.x = (size.x / 6) + position.x;
	textPosition.y = (size.y / 4) + position.y;
    font.loadFromFile("..\\Font\\Roboto-VariableFont_wdth,wght.ttf");
    buttonText.setFont(font);
	buttonText.setPosition(textPosition);
    buttonText.setFillColor(Color::Black);
    buttonText.setString(text);
	this->destination = destination;
}

void Button::update(RenderWindow& window)
{
    if (active)
    {

        if (Mouse::isButtonPressed(Mouse::Left))
        {
            if (released)
            {
                clicked = true;
            }
            released = false;

        }
        window.draw(buttonSprite);
        window.draw(buttonText);
    }
}
