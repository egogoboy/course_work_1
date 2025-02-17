#ifndef MYSPRITE_H
#define MYSPRITE_H
#include <SFML/Graphics.hpp>
#include <map>

class MySprite {
    public:

        MySprite() {}

        MySprite(std::string fileName) {
            texture.loadFromFile(fileName);
            textures[fileName] = texture;
            this -> sprite.setTexture(textures[fileName]);
        }

        void setPosition(float x, float y);
        void setPosition(std::pair<int, int>);
        void setScale(float scale);
        void setTexture(std::string fileName);

        sf::Sprite getSprite();

    protected:

    private:
        sf::Sprite sprite;
        float x_, y_;

        static inline sf::Texture texture;
        static inline std::map<std::string, sf::Texture> textures;
};

#endif
