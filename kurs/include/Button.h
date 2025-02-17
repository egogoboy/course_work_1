#ifndef BUTTON_H
#define BUTTON_H
#include <SFML/Graphics.hpp>

class Button
{
    public:
        Button() {
            x_ = 0.0;
            y_ = 0.0;
            xSize_ = 0.0;
            ySize_ = 0.0;
            buttonGlow_.setFillColor(sf::Color(0, 0, 0, 0));
        }

        Button(float x, float y, float xSize, float ySize) {
            x_ = x;
            y_ = y;
            xSize_ = xSize;
            ySize_ = ySize;
            isPress_ = false;
            body_.setPosition(sf::Vector2f(x, y));
            body_.setSize(sf::Vector2f(xSize, ySize));
            buttonGlow_.setPosition(sf::Vector2f(x, y));
            buttonGlow_.setSize(sf::Vector2f(xSize, ySize));
            buttonGlow_.setFillColor(sf::Color(0, 0, 0, 0));
        }

        void setColor(sf::Color color);
        void setBorderColor(sf::Color color);
        void setBorderSize(float borderSize);
        void setTexture(sf::Texture texture);
        void setFillTexture(sf::Texture texture);
        void setPosition(float x, float y);
        void setSize(float x, float y);
        void setAllOptions(float xPos, float yPos, float xSize, float ySize);

        bool isPressed(sf::RenderWindow& app);
        bool isMouseInButton(sf::Vector2i mousePosition);

        void drawButton(sf::RenderWindow& app);

        sf::RectangleShape getButton();

    protected:

    private:
        float x_,
              y_,
              xSize_,
              ySize_;

        sf::Vector2i mousePressPosition_;
        bool isPress_;
        sf::RectangleShape body_,
                           buttonGlow_;

        sf::Text buttonText_;

};

#endif
