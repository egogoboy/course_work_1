#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "include/Maze.h"
#include "include/Interface.h"

using namespace sf;

int main() {

    setlocale(LC_ALL, "RUS");
    RenderWindow app(VideoMode(1280, 720), "BackTracking");

    Maze maze(10);
    UserInterface interface(maze);

    while (app.isOpen()) {

        interface.updateUserInterface(app, maze);

        app.clear(Color::White);

        interface.drawUserInterface(app, maze);

        app.display();
    }

    return EXIT_SUCCESS;
}
