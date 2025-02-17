#ifndef BACKTRACKING_H
#define BACKTRACKING_H
#include <SFML/Graphics.hpp>
#include <Maze.h>

class BackTracking
{
    public:
        static startBackTraking(sf::RenderWindow& app);

    protected:

    private:
        static backTraking(sf::RenderWindow& app);
        std::pair<int, int> unitPosition_;
};

#endif // BACKTRACKING_H
