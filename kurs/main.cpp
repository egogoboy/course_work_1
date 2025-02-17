#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <vector>
#include <Maze.h>
#include <MazeGeneration.h>
#include <BackTraking.h>
#include <Interface.h>

using namespace sf;

int main() {

    setlocale(LC_ALL, "RUS");
    RenderWindow app(VideoMode(1280, 720), "Поиск выхода из двумерного лабиринта методом бэктрекинга"/*, sf::Style::Fullscreen*/);

    //Создание стартового лабиринта
    Maze maze(10);
    UserInterface interface(maze);

    // Основной цикл программы
    while (app.isOpen()) {

        //Обработка взаимодействия пользователя с интерфейсом
        interface.updateUserInterface(app, maze);

        app.clear(Color::White);

        //Отрисовка интерфейса
        interface.drawUserInterface(app, maze);

        app.display();
    }

    return EXIT_SUCCESS;
}
