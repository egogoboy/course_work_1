#include "../include/MySprite.h"

void MySprite::setPosition(float x, float y) {
     x_ = x;
     y_ = y;
     sprite.setPosition(x, y);
}

void MySprite::setPosition(std::pair<int, int> pos) {
    x_ = pos.first;
    y_ = pos.second;
}

void MySprite::setScale(float scale) {
     sprite.scale(1 / sprite.getScale().x, 1 / sprite.getScale().y);
     sprite.scale(scale, scale);
}

sf::Sprite MySprite::getSprite() {
    return  sprite;
}

void MySprite::setTexture(std::string fileName) {
    texture.loadFromFile(fileName);
    textures[fileName] = texture;
    this -> sprite.setTexture(textures[fileName]);
}
