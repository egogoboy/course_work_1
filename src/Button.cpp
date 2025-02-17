#include "../include/Button.h"

void Button::drawButton(sf::RenderWindow& app) {
    app.draw(body_);
    app.draw(buttonText_);
    app.draw(buttonGlow_);
}

void Button::setColor(sf::Color color) {
    body_.setFillColor(color);
}

void Button::setBorderColor(sf::Color color) {
    body_.setOutlineColor(color);
}

void Button::setBorderSize(float borderSize) {
    body_.setOutlineThickness(borderSize);
}

void Button::setFillTexture(sf::Texture texture) {
    body_.setTexture(&texture);
}

void Button::setPosition(float x, float y) {
    x_ = x;
    y_ = y;
    body_.setPosition(sf::Vector2f(x, y));
    buttonGlow_.setPosition(sf::Vector2f(x, y));
}

void Button::setSize(float x, float y) {
    xSize_ = x;
    ySize_ = y;
    body_.setSize(sf::Vector2f(xSize_, ySize_));
    buttonGlow_.setSize(sf::Vector2f(xSize_, ySize_));
}

void Button::setAllOptions(float xPos, float yPos, float xSize, float ySize) {
    setPosition(xPos, yPos);
    setSize(xSize, ySize);
    setColor(sf::Color::White);
    setBorderSize(7);
    setBorderColor(sf::Color::Black);
}

sf::RectangleShape Button::getButton() {
    return body_;
}

bool Button::isPressed(sf::RenderWindow& app) {

    if (!isPress_ && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        mousePressPosition_ = sf::Mouse::getPosition(app);
        isPress_ = true;
        if (isMouseInButton(sf::Mouse::getPosition(app)) && isMouseInButton(mousePressPosition_))
            buttonGlow_.setFillColor(sf::Color(0, 0, 0, 40));
    }

    if (isPress_ && !(sf::Mouse::isButtonPressed(sf::Mouse::Left))) {
        isPress_ = false;
        if (isMouseInButton(sf::Mouse::getPosition(app)) && isMouseInButton(mousePressPosition_)) {
            buttonGlow_.setFillColor(sf::Color(0, 0, 0, 0));
            return true;
        }
        buttonGlow_.setFillColor(sf::Color(0, 0, 0, 0));
    }

    return false;

}

bool Button::isMouseInButton(sf::Vector2i mousePosition) {

    return ((mousePosition.x >= x_) && (mousePosition.x <= x_+ xSize_
        && mousePosition.y >= y_) && (mousePosition.y <= y_ + ySize_));

}
