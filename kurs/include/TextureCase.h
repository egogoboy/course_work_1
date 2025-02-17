#ifndef TEXTURECASE_H
#define TEXTURECASE_H
#include <map>
#include <SFML/Graphics/Texture.hpp>

class TextureCase {
    public:

        static std::map<std::string, sf::Texture> textures;

        static void addTexture(std::string textureName, std::string fileName) {
            sf::Texture temp;
            temp.loadFromFile(fileName);
        //  if (temp.loadFromFile())
            textures[textureName] = temp;
        }

        static sf::Texture getTexture(std::string textureName) {
            return textures[textureName];
        }

    protected:

    private:

};

#endif
